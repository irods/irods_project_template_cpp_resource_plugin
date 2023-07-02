#include "irods/msParam.h"
#include "irods/miscServerFunct.hpp"

#include "irods/irods_resource_plugin.hpp"
#include "irods/irods_file_object.hpp"
#include "irods/irods_collection_object.hpp"
#include "irods/irods_string_tokenize.hpp"
#include "irods/irods_hierarchy_parser.hpp"
#include "irods/irods_error.hpp"
#include "irods/irods_kvp_string_parser.hpp"
#include "irods/irods_resource_redirect.hpp"
#include "irods/irods_lexical_cast.hpp"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <boost/lexical_cast.hpp>

#include <sys/vfs.h>
#include <sys/stat.h>

#include <string.h>


namespace {

	using log_server = irods::experimental::log::server;

	auto log_plugin_op(const char* _fn) {
	    log_server::debug(std::string("resource_plugin-noop ")+_fn);
	    return SUCCESS();
	}

	auto file_create(irods::plugin_context& _ctx) {
	    return log_plugin_op(__FUNCTION__);
	} // file_create

	auto file_open(irods::plugin_context& _ctx) {
	    
	    return log_plugin_op(__FUNCTION__);
	} // file_open

	auto file_read(
	    irods::plugin_context& _ctx,
	    void*                  _buf,
	    const int              _len ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_read

	auto file_write(
	    irods::plugin_context& _ctx,
	    const void*            _buf,
	    const int              _len ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_write

	auto file_close( irods::plugin_context& _ctx ) {
	    
	    return log_plugin_op(__FUNCTION__);
	} // file_close

	auto file_unlink( irods::plugin_context& _ctx ) {
	    
	    return log_plugin_op(__FUNCTION__);
	} // file_unlink

	auto file_stat(
	    irods::plugin_context& _ctx,
	    struct stat*           _statbuf ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_stat

	auto file_lseek(
	    irods::plugin_context& _ctx,
	    const long long        _offset,
	    const int              _whence ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_lseek

	auto file_mkdir(irods::plugin_context& _ctx) {
	    return log_plugin_op(__FUNCTION__);
	} // file_mkdir

	auto file_rmdir( irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_rmdir

	auto file_opendir( irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_opendir_plugin

	auto file_closedir( irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_closedir_plugin

	auto file_readdir(
	    irods::plugin_context& _ctx,
	    struct rodsDirent**    _dirent_ptr ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_readdir_plugin

	auto file_rename(
	    irods::plugin_context& _ctx,
	    const char*            _new_file_name ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_rename_plugin

	auto file_truncate(irods::plugin_context& _ctx) {
	    
	    return log_plugin_op(__FUNCTION__);
	} // file_truncate_plugin

	auto file_getfs_freespace(irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_getfs_freespace

	auto file_stage_to_cache(
	    irods::plugin_context& _ctx,
	    const char*            _cache_file_name ) {
	    return log_plugin_op(__FUNCTION__);
	} // stage_to_cache

	auto file_sync_to_arch(
	    irods::plugin_context& _ctx,
	    const char*            _cache_file_name ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_sync_to_arch

	auto file_registered( irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_registered

	auto file_unregistered( irods::plugin_context& _ctx) {
	    return log_plugin_op(__FUNCTION__);
	} // file_unregistered

	auto file_modified( irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_modified

	auto file_resolve_hierarchy(
	    irods::plugin_context&   _ctx,
	    const std::string*       _opr,
	    const std::string*       _curr_host,
	    irods::hierarchy_parser* _out_parser,
	    float*                   _out_vote ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_resolve_hierarchy

	auto file_rebalance( irods::plugin_context& _ctx ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_rebalance

	auto file_notify(
	    irods::plugin_context& _ctx,
	    const std::string*     _opr ) {
	    return log_plugin_op(__FUNCTION__);
	} // file_notify

} // anonymous namespace

extern "C" auto plugin_factory(
		const std::string& _inst_name,
		const std::string& _context ) -> irods::resource* {

    using namespace irods;
    using namespace std;

    auto* resc = new irods::resource( _inst_name, _context );

    resc->add_operation(
        RESOURCE_OP_CREATE,
        function<error(plugin_context&)>(
            file_create ) );

    resc->add_operation(
        irods::RESOURCE_OP_OPEN,
        function<error(plugin_context&)>(
            file_open ) );

    resc->add_operation(
        irods::RESOURCE_OP_READ,
        std::function<
            error(irods::plugin_context&,void*,const int)>(
                file_read ) );

    resc->add_operation(
        irods::RESOURCE_OP_WRITE,
        function<error(plugin_context&,const void*,const int)>(
            file_write ) );

    resc->add_operation(
        RESOURCE_OP_CLOSE,
        function<error(plugin_context&)>(
            file_close ) );

    resc->add_operation(
        irods::RESOURCE_OP_UNLINK,
        function<error(plugin_context&)>(
            file_unlink ) );

    resc->add_operation(
        irods::RESOURCE_OP_STAT,
        function<error(plugin_context&, struct stat*)>(
            file_stat ) );

    resc->add_operation(
        irods::RESOURCE_OP_MKDIR,
        function<error(plugin_context&)>(
            file_mkdir ) );

    resc->add_operation(
        irods::RESOURCE_OP_OPENDIR,
        function<error(plugin_context&)>(
            file_opendir ) );

    resc->add_operation(
        irods::RESOURCE_OP_READDIR,
        function<error(plugin_context&,struct rodsDirent**)>(
            file_readdir ) );

    resc->add_operation(
        irods::RESOURCE_OP_RENAME,
        function<error(plugin_context&, const char*)>(
            file_rename ) );

    resc->add_operation(
        irods::RESOURCE_OP_FREESPACE,
        function<error(plugin_context&)>(
            file_getfs_freespace ) );

    resc->add_operation(
        irods::RESOURCE_OP_LSEEK,
        function<error(plugin_context&, const long long, const int)>(
            file_lseek ) );

    resc->add_operation(
        irods::RESOURCE_OP_RMDIR,
        function<error(plugin_context&)>(
            file_rmdir ) );

    resc->add_operation(
        irods::RESOURCE_OP_CLOSEDIR,
        function<error(plugin_context&)>(
            file_closedir ) );

    resc->add_operation(
        irods::RESOURCE_OP_STAGETOCACHE,
        function<error(plugin_context&, const char*)>(
            file_stage_to_cache ) );

    resc->add_operation(
        irods::RESOURCE_OP_SYNCTOARCH,
        function<error(plugin_context&, const char*)>(
            file_sync_to_arch ) );

    resc->add_operation(
        irods::RESOURCE_OP_REGISTERED,
        function<error(plugin_context&)>(
            file_registered ) );

    resc->add_operation(
        irods::RESOURCE_OP_UNREGISTERED,
        function<error(plugin_context&)>(
            file_unregistered ) );

    resc->add_operation(
        irods::RESOURCE_OP_MODIFIED,
        function<error(plugin_context&)>(
            file_modified ) );

    resc->add_operation(
        irods::RESOURCE_OP_NOTIFY,
        function<error(plugin_context&, const std::string*)>(
            file_notify ) );

    resc->add_operation(
        irods::RESOURCE_OP_TRUNCATE,
        function<error(plugin_context&)>(
            file_truncate ) );

    resc->add_operation(
        irods::RESOURCE_OP_RESOLVE_RESC_HIER,
        function<error(plugin_context&,const std::string*, const std::string*, irods::hierarchy_parser*, float*)>(
            file_resolve_hierarchy ) );

    resc->add_operation(
        irods::RESOURCE_OP_REBALANCE,
        function<error(plugin_context&)>(
            file_rebalance ) );

    resc->set_property< int >( irods::RESOURCE_CHECK_PATH_PERM, 2 );
    resc->set_property< int >( irods::RESOURCE_CREATE_PATH,     1 );

    return resc;

} // plugin_factory


