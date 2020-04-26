/*
Copyright (c) 2012-2014 The SSDB Authors. All rights reserved.
Use of this source code is governed by a BSD-style license that can be
found in the LICENSE file.
*/
#include "worker.h"
#include "link.h"
#include "proc.h"
#include "../util/log.h"
#include "../include.h"

ProcWorker::ProcWorker(const std::string &name){
	this->name = name;
}

void ProcWorker::init(){
	log_debug("%s %d init", this->name.c_str(), this->id);
}

int ProcWorker::proc(ProcJob *job){
	log_debug("start worker proc");
	const Request *req = job->req;
	
	proc_t p = job->cmd->proc;
	job->time_wait = 1000 * (microtime() - job->stime);
	job->result = (*p)(job->serv, job->link, *req, &job->resp);
	job->time_proc = 1000 * (microtime() - job->stime) - job->time_wait;
	log_debug("ProcWorker::proc: w:%.3f,p:%.3f, req: %s, resp: %s",
				job->time_wait, job->time_proc,
				serialize_req(*job->req).c_str(),
				serialize_req(job->resp.resp).c_str());
	if(job->link->send(job->resp.resp) == -1){
		job->result = PROC_ERROR;
	}else{
		// try to write socket before it would be added to fdevents
		// socket is NONBLOCK, so it won't block.
		log_debug("start write to clinet ..............");
		if(job->link->write() < 0){
			job->result = PROC_ERROR;
		}
		log_debug("end write to clinet ..............");
	}
	log_debug("end worker proc");

	return 0;
}
