/* -*- Mode: C; tab-width: 4; c-basic-offset: 4; indent-tabs-mode: nil -*- */
#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/time.h>
#include <assert.h>
#include "mcs.h"

// The following is abuse of private internals from libmemcached!!!!
// Using these symbols doesn't work if you try to link with a shared
// version of libmemcached, so you need an archive
// It should be fixed ASAP
extern void* memcached_server_instance_fetch(memcached_st *ptr,
                                             uint32_t server_key);
extern void memcached_quit_server(memcached_server_st *ptr, bool io_death);
extern memcached_return_t memcached_connect(void* ptr);
extern memcached_return_t memcached_do(void *ptr, const void *command,
                                       size_t command_length,
                                       bool with_flush);
extern ssize_t memcached_io_write(void *ptr, const void *buffer,
                                  size_t length, bool with_flush);
extern memcached_return_t memcached_safe_read(void *ptr, void *dta,
                                              size_t size);
extern void memcached_io_reset(void *ptr);
// END libmemcached hack


mcs_st *mcs_create(mcs_st *ptr) {
    return memcached_create(ptr);
}

void mcs_free(mcs_st *ptr) {
    memcached_free(ptr);
}

mcs_return mcs_behavior_set(mcs_st *ptr, memcached_behavior flag, uint64_t data) {
    return memcached_behavior_set(ptr, flag, data);
}

uint32_t mcs_server_count(mcs_st *ptr) {
    return memcached_server_count(ptr);
}

mcs_return mcs_server_push(mcs_st *ptr, mcs_server_st *list) {
    return memcached_server_push(ptr, list);
}

mcs_server_st *mcs_server_index(mcs_st *ptr, int i) {
    return memcached_server_instance_fetch(ptr, i);
}

uint32_t mcs_key_hash(mcs_st *ptr, const char *key, size_t key_length) {
    return memcached_generate_hash(ptr, key, key_length);
}

mcs_server_st *mcs_server_st_parse(const char *str_servers) {
    return memcached_servers_parse(str_servers); // Ex: "host:port,host2:port2"
}

void mcs_server_st_free(mcs_server_st *ptr) {
    memcached_server_list_free(ptr);
}

void mcs_server_st_quit(mcs_server_st *ptr, uint8_t io_death) {
    memcached_quit_server(ptr, io_death);
}

mcs_return mcs_server_st_connect(mcs_server_st *ptr) {
    return memcached_connect(ptr);
}

mcs_return mcs_server_st_do(mcs_server_st *ptr,
                            const void *command,
                            size_t command_length,
                            uint8_t with_flush) {
    return memcached_do(ptr, command, command_length, with_flush);
}

ssize_t mcs_server_st_io_write(mcs_server_st *ptr,
                               const void *buffer,
                               size_t length,
                               char with_flush) {
    return memcached_io_write(ptr, buffer, length, with_flush);
}

mcs_return mcs_server_st_read(mcs_server_st *ptr,
                              void *dta,
                              size_t size) {
    return memcached_safe_read(ptr, dta, size);
}

void mcs_server_st_io_reset(mcs_server_st *ptr) {
    memcached_io_reset(ptr);
}

const char *mcs_server_st_hostname(mcs_server_st *ptr) {
    return ptr->hostname;
}

int mcs_server_st_port(mcs_server_st *ptr) {
    return ptr->port;
}

int mcs_server_st_fd(mcs_server_st *ptr) {
    return ptr->fd;
}

