/* 
 * Skeleton VFS module.  Implements passthrough operation of all VFS
 * calls to disk functions.
 *
 * Copyright (C) Tim Potter, 1999-2000
 * Copyright (C) Alexander Bokovoy, 2002
 * Copyright (C) Stefan (metze) Metzmacher, 2003
 * Copyright (C) Jeremy Allison 2009
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *  
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *  
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "../source3/include/includes.h"
#include "lib/util/tevent_unix.h"
#include "lib/util/tevent_ntstatus.h"

/* PLEASE,PLEASE READ THE VFS MODULES CHAPTER OF THE 
   SAMBA DEVELOPERS GUIDE!!!!!!
 */

/* If you take this file as template for your module
 * please make sure that you remove all bifrost_XXX() functions you don't
 * want to implement!! The passthrough operations are not
 * neccessary in a real module.
 *
 * --metze
 */
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>


#include <fcntl.h>           /* Definition of AT_* constants */
#include <sys/stat.h>


static FILE  *  vfs_bifrost_log = NULL;


static
void
bifrost_log
  (const char *msg)
{

	if(vfs_bifrost_log==NULL) {
		vfs_bifrost_log = fopen("/home/gsilverman/vfs_bifrost_log.txt","a");
	}
	fprintf(vfs_bifrost_log,"%s\n",msg);
	fflush(vfs_bifrost_log);
}

static int bifrost_connect(vfs_handle_struct *handle, const char *service,
			const char *user)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CONNECT(handle, service, user);
}

static void bifrost_disconnect(vfs_handle_struct *handle)
{
	bifrost_log(__FUNCTION__);
	SMB_VFS_NEXT_DISCONNECT(handle);
}

static uint64_t bifrost_disk_free(vfs_handle_struct *handle, const char *path,
			       bool small_query, uint64_t *bsize,
			       uint64_t *dfree, uint64_t *dsize)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_DISK_FREE(handle, path, small_query, bsize,
				      dfree, dsize);
}

static int bifrost_get_quota(vfs_handle_struct *handle, enum SMB_QUOTA_TYPE qtype,
			  unid_t id, SMB_DISK_QUOTA *dq)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GET_QUOTA(handle, qtype, id, dq);
}

static int bifrost_set_quota(vfs_handle_struct *handle, enum SMB_QUOTA_TYPE qtype,
			  unid_t id, SMB_DISK_QUOTA *dq)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SET_QUOTA(handle, qtype, id, dq);
}

static int bifrost_get_shadow_copy_data(vfs_handle_struct *handle,
				     files_struct *fsp,
				     struct shadow_copy_data *shadow_copy_data,
				     bool labels)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GET_SHADOW_COPY_DATA(handle, fsp, shadow_copy_data,
						 labels);
}

static int bifrost_statvfs(struct vfs_handle_struct *handle, const char *path,
			struct vfs_statvfs_struct *statbuf)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_STATVFS(handle, path, statbuf);
}

static uint32_t bifrost_fs_capabilities(struct vfs_handle_struct *handle,
				     enum timestamp_set_resolution *p_ts_res)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FS_CAPABILITIES(handle, p_ts_res);
}

static NTSTATUS bifrost_get_dfs_referrals(struct vfs_handle_struct *handle,
				       struct dfs_GetDFSReferral *r)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GET_DFS_REFERRALS(handle, r);
}

static DIR *bifrost_opendir(vfs_handle_struct *handle, const char *fname,
			 const char *mask, uint32 attr)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_OPENDIR(handle, fname, mask, attr);
}

static DIR *bifrost_fdopendir(vfs_handle_struct *handle, files_struct *fsp,
			   const char *mask, uint32 attr)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FDOPENDIR(handle, fsp, mask, attr);
}

static struct dirent *bifrost_readdir(vfs_handle_struct *handle,
				   DIR *dirp, SMB_STRUCT_STAT *sbuf)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_READDIR(handle, dirp, sbuf);
}

static void bifrost_seekdir(vfs_handle_struct *handle, DIR *dirp, long offset)
{
	bifrost_log(__FUNCTION__);
	SMB_VFS_NEXT_SEEKDIR(handle, dirp, offset);
}

static long bifrost_telldir(vfs_handle_struct *handle, DIR *dirp)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_TELLDIR(handle, dirp);
}

static void bifrost_rewind_dir(vfs_handle_struct *handle, DIR *dirp)
{
	SMB_VFS_NEXT_REWINDDIR(handle, dirp);
}

static int bifrost_mkdir(vfs_handle_struct *handle, const char *path, mode_t mode)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_MKDIR(handle, path, mode);
}

static int bifrost_rmdir(vfs_handle_struct *handle, const char *path)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_RMDIR(handle, path);
}

static int bifrost_closedir(vfs_handle_struct *handle, DIR *dir)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CLOSEDIR(handle, dir);
}

static void vfs_bifrost_init_search_op(struct vfs_handle_struct *handle, DIR *dirp)
{
	bifrost_log(__FUNCTION__);
	SMB_VFS_NEXT_INIT_SEARCH_OP(handle, dirp);
}

static int bifrost_open(vfs_handle_struct *handle, struct smb_filename *smb_fname,
		     files_struct *fsp, int flags, mode_t mode)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_OPEN(handle, smb_fname, fsp, flags, mode);
}

static NTSTATUS bifrost_create_file(struct vfs_handle_struct *handle,
				 struct smb_request *req,
				 uint16_t root_dir_fid,
				 struct smb_filename *smb_fname,
				 uint32_t access_mask,
				 uint32_t share_access,
				 uint32_t create_disposition,
				 uint32_t create_options,
				 uint32_t file_attributes,
				 uint32_t oplock_request,
				 uint64_t allocation_size,
				 uint32_t private_flags,
				 struct security_descriptor *sd,
				 struct ea_list *ea_list,
				 files_struct ** result, int *pinfo)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CREATE_FILE(handle,
					req,
					root_dir_fid,
					smb_fname,
					access_mask,
					share_access,
					create_disposition,
					create_options,
					file_attributes,
					oplock_request,
					allocation_size,
					private_flags,
					sd, ea_list, result, pinfo);
}

static int bifrost_close_fn(vfs_handle_struct *handle, files_struct *fsp)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CLOSE(handle, fsp);
}

static ssize_t bifrost_vfs_read(vfs_handle_struct *handle, files_struct *fsp,
			     void *data, size_t n)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_READ(handle, fsp, data, n);
}

static ssize_t bifrost_pread(vfs_handle_struct *handle, files_struct *fsp,
			  void *data, size_t n, off_t offset)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_PREAD(handle, fsp, data, n, offset);
}

struct bifrost_pread_state {
	ssize_t ret;
	int err;
};

static void bifrost_pread_done(struct tevent_req *subreq);

static struct tevent_req *bifrost_pread_send(struct vfs_handle_struct *handle,
					  TALLOC_CTX *mem_ctx,
					  struct tevent_context *ev,
					  struct files_struct *fsp,
					  void *data, size_t n, off_t offset)
{
	struct tevent_req *req, *subreq;
	struct bifrost_pread_state *state;

	bifrost_log(__FUNCTION__);
	req = tevent_req_create(mem_ctx, &state, struct bifrost_pread_state);
	if (req == NULL) {
		return NULL;
	}
	subreq = SMB_VFS_NEXT_PREAD_SEND(state, ev, handle, fsp, data,
					 n, offset);
	if (tevent_req_nomem(subreq, req)) {
		return tevent_req_post(req, ev);
	}
	tevent_req_set_callback(subreq, bifrost_pread_done, req);
	return req;
}

static void bifrost_pread_done(struct tevent_req *subreq)
{
	struct tevent_req *req =
	    tevent_req_callback_data(subreq, struct tevent_req);
	struct bifrost_pread_state *state =
	    tevent_req_data(req, struct bifrost_pread_state);

	bifrost_log(__FUNCTION__);
	state->ret = SMB_VFS_PREAD_RECV(subreq, &state->err);
	TALLOC_FREE(subreq);
	tevent_req_done(req);
}

static ssize_t bifrost_pread_recv(struct tevent_req *req, int *err)
{
	struct bifrost_pread_state *state =
	    tevent_req_data(req, struct bifrost_pread_state);

	bifrost_log(__FUNCTION__);
	if (tevent_req_is_unix_error(req, err)) {
		return -1;
	}
	*err = state->err;
	return state->ret;
}

static ssize_t bifrost_write(vfs_handle_struct *handle, files_struct *fsp,
			  const void *data, size_t n)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_WRITE(handle, fsp, data, n);
}

static ssize_t bifrost_pwrite(vfs_handle_struct *handle, files_struct *fsp,
			   const void *data, size_t n, off_t offset)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_PWRITE(handle, fsp, data, n, offset);
}

struct bifrost_pwrite_state {
	ssize_t ret;
	int err;
};

static void bifrost_pwrite_done(struct tevent_req *subreq);

static struct tevent_req *bifrost_pwrite_send(struct vfs_handle_struct *handle,
					   TALLOC_CTX *mem_ctx,
					   struct tevent_context *ev,
					   struct files_struct *fsp,
					   const void *data,
					   size_t n, off_t offset)
{
	struct tevent_req *req, *subreq;
	struct bifrost_pwrite_state *state;

	bifrost_log(__FUNCTION__);
	req = tevent_req_create(mem_ctx, &state, struct bifrost_pwrite_state);
	if (req == NULL) {
		return NULL;
	}
	subreq = SMB_VFS_NEXT_PWRITE_SEND(state, ev, handle, fsp, data,
					  n, offset);
	if (tevent_req_nomem(subreq, req)) {
		return tevent_req_post(req, ev);
	}
	tevent_req_set_callback(subreq, bifrost_pwrite_done, req);
	return req;
}

static void bifrost_pwrite_done(struct tevent_req *subreq)
{
	struct tevent_req *req =
	    tevent_req_callback_data(subreq, struct tevent_req);
	struct bifrost_pwrite_state *state =
	    tevent_req_data(req, struct bifrost_pwrite_state);

	bifrost_log(__FUNCTION__);
	state->ret = SMB_VFS_PWRITE_RECV(subreq, &state->err);
	TALLOC_FREE(subreq);
	tevent_req_done(req);
}

static ssize_t bifrost_pwrite_recv(struct tevent_req *req, int *err)
{
	struct bifrost_pwrite_state *state =
	    tevent_req_data(req, struct bifrost_pwrite_state);

	bifrost_log(__FUNCTION__);
	if (tevent_req_is_unix_error(req, err)) {
		return -1;
	}
	*err = state->err;
	return state->ret;
}

static off_t bifrost_lseek(vfs_handle_struct *handle, files_struct *fsp,
			off_t offset, int whence)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LSEEK(handle, fsp, offset, whence);
}

static ssize_t bifrost_sendfile(vfs_handle_struct *handle, int tofd,
			     files_struct *fromfsp, const DATA_BLOB *hdr,
			     off_t offset, size_t n)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SENDFILE(handle, tofd, fromfsp, hdr, offset, n);
}

static ssize_t bifrost_recvfile(vfs_handle_struct *handle, int fromfd,
			     files_struct *tofsp, off_t offset, size_t n)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_RECVFILE(handle, fromfd, tofsp, offset, n);
}

static int bifrost_rename(vfs_handle_struct *handle,
		       const struct smb_filename *smb_fname_src,
		       const struct smb_filename *smb_fname_dst)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_RENAME(handle, smb_fname_src, smb_fname_dst);
}

static int bifrost_fsync(vfs_handle_struct *handle, files_struct *fsp)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FSYNC(handle, fsp);
}

struct bifrost_fsync_state {
	int ret;
	int err;
};

static void bifrost_fsync_done(struct tevent_req *subreq);

static struct tevent_req *bifrost_fsync_send(struct vfs_handle_struct *handle,
					  TALLOC_CTX *mem_ctx,
					  struct tevent_context *ev,
					  struct files_struct *fsp)
{
	struct tevent_req *req, *subreq;
	struct bifrost_fsync_state *state;

	bifrost_log(__FUNCTION__);
	req = tevent_req_create(mem_ctx, &state, struct bifrost_fsync_state);
	if (req == NULL) {
		return NULL;
	}
	subreq = SMB_VFS_NEXT_FSYNC_SEND(state, ev, handle, fsp);
	if (tevent_req_nomem(subreq, req)) {
		return tevent_req_post(req, ev);
	}
	tevent_req_set_callback(subreq, bifrost_fsync_done, req);
	return req;
}

static void bifrost_fsync_done(struct tevent_req *subreq)
{
	struct tevent_req *req =
	    tevent_req_callback_data(subreq, struct tevent_req);
	struct bifrost_fsync_state *state =
	    tevent_req_data(req, struct bifrost_fsync_state);

	bifrost_log(__FUNCTION__);
	state->ret = SMB_VFS_FSYNC_RECV(subreq, &state->err);
	TALLOC_FREE(subreq);
	tevent_req_done(req);
}

static int bifrost_fsync_recv(struct tevent_req *req, int *err)
{
	struct bifrost_fsync_state *state =
	    tevent_req_data(req, struct bifrost_fsync_state);

	bifrost_log(__FUNCTION__);
	if (tevent_req_is_unix_error(req, err)) {
		return -1;
	}
	*err = state->err;
	return state->ret;
}

static int bifrost_stat(vfs_handle_struct *handle, struct smb_filename *smb_fname)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_STAT(handle, smb_fname);
}

static int bifrost_fstat(vfs_handle_struct *handle, files_struct *fsp,
		      SMB_STRUCT_STAT *sbuf)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FSTAT(handle, fsp, sbuf);
}

static int bifrost_lstat(vfs_handle_struct *handle,
		      struct smb_filename *smb_fname)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LSTAT(handle, smb_fname);
}

static uint64_t bifrost_get_alloc_size(struct vfs_handle_struct *handle,
				    struct files_struct *fsp,
				    const SMB_STRUCT_STAT *sbuf)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GET_ALLOC_SIZE(handle, fsp, sbuf);
}

static int bifrost_unlink(vfs_handle_struct *handle,
		       const struct smb_filename *smb_fname)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_UNLINK(handle, smb_fname);
}

static int bifrost_chmod(vfs_handle_struct *handle, const char *path, mode_t mode)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CHMOD(handle, path, mode);
}

static int bifrost_fchmod(vfs_handle_struct *handle, files_struct *fsp,
		       mode_t mode)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FCHMOD(handle, fsp, mode);
}

static int bifrost_chown(vfs_handle_struct *handle, const char *path, uid_t uid,
		      gid_t gid)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CHOWN(handle, path, uid, gid);
}

static int bifrost_fchown(vfs_handle_struct *handle, files_struct *fsp,
		       uid_t uid, gid_t gid)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FCHOWN(handle, fsp, uid, gid);
}

static int bifrost_lchown(vfs_handle_struct *handle, const char *path, uid_t uid,
		       gid_t gid)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LCHOWN(handle, path, uid, gid);
}

static int bifrost_chdir(vfs_handle_struct *handle, const char *path)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CHDIR(handle, path);
}

static char *bifrost_getwd(vfs_handle_struct *handle)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GETWD(handle);
}

static int bifrost_ntimes(vfs_handle_struct *handle,
		       const struct smb_filename *smb_fname,
		       struct smb_file_time *ft)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_NTIMES(handle, smb_fname, ft);
}

static int bifrost_ftruncate(vfs_handle_struct *handle, files_struct *fsp,
			  off_t offset)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FTRUNCATE(handle, fsp, offset);
}

static int bifrost_fallocate(vfs_handle_struct *handle, files_struct *fsp,
			  enum vfs_fallocate_mode mode, off_t offset, off_t len)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FALLOCATE(handle, fsp, mode, offset, len);
}

static bool bifrost_lock(vfs_handle_struct *handle, files_struct *fsp, int op,
		      off_t offset, off_t count, int type)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LOCK(handle, fsp, op, offset, count, type);
}

static int bifrost_kernel_flock(struct vfs_handle_struct *handle,
			     struct files_struct *fsp, uint32 share_mode,
			     uint32 access_mask)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_KERNEL_FLOCK(handle, fsp, share_mode, access_mask);
}

static int bifrost_linux_setlease(struct vfs_handle_struct *handle,
			       struct files_struct *fsp, int leasetype)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LINUX_SETLEASE(handle, fsp, leasetype);
}

static bool bifrost_getlock(vfs_handle_struct *handle, files_struct *fsp,
			 off_t *poffset, off_t *pcount, int *ptype,
			 pid_t *ppid)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GETLOCK(handle, fsp, poffset, pcount, ptype, ppid);
}

static int bifrost_symlink(vfs_handle_struct *handle, const char *oldpath,
			const char *newpath)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYMLINK(handle, oldpath, newpath);
}

static int bifrost_vfs_readlink(vfs_handle_struct *handle, const char *path,
			     char *buf, size_t bufsiz)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_READLINK(handle, path, buf, bufsiz);
}

static int bifrost_link(vfs_handle_struct *handle, const char *oldpath,
		     const char *newpath)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LINK(handle, oldpath, newpath);
}

static int bifrost_mknod(vfs_handle_struct *handle, const char *path, mode_t mode,
		      SMB_DEV_T dev)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_MKNOD(handle, path, mode, dev);
}

static char *bifrost_realpath(vfs_handle_struct *handle, const char *path)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_REALPATH(handle, path);
}

static NTSTATUS bifrost_notify_watch(struct vfs_handle_struct *handle,
				  struct sys_notify_context *ctx,
				  const char *path,
				  uint32_t *filter,
				  uint32_t *subdir_filter,
				  void (*callback) (struct sys_notify_context *ctx,
						    void *private_data,
						    struct notify_event *ev),
				  void *private_data, void *handle_p)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_NOTIFY_WATCH(handle, ctx, path,
					 filter, subdir_filter, callback,
					 private_data, handle_p);
}

static int bifrost_chflags(vfs_handle_struct *handle, const char *path,
			uint flags)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CHFLAGS(handle, path, flags);
}

static struct file_id bifrost_file_id_create(vfs_handle_struct *handle,
					  const SMB_STRUCT_STAT *sbuf)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FILE_ID_CREATE(handle, sbuf);
}

struct bifrost_cc_state {
	struct vfs_handle_struct *handle;
	off_t copied;
};
static void bifrost_copy_chunk_done(struct tevent_req *subreq);

static struct tevent_req *bifrost_copy_chunk_send(struct vfs_handle_struct *handle,
					       TALLOC_CTX *mem_ctx,
					       struct tevent_context *ev,
					       struct files_struct *src_fsp,
					       off_t src_off,
					       struct files_struct *dest_fsp,
					       off_t dest_off,
					       off_t num)
{
	struct tevent_req *req;
	struct tevent_req *subreq;
	struct bifrost_cc_state *cc_state;
	bifrost_log(__FUNCTION__);

	req = tevent_req_create(mem_ctx, &cc_state, struct bifrost_cc_state);
	if (req == NULL) {
		return NULL;
	}

	cc_state->handle = handle;
	subreq = SMB_VFS_NEXT_COPY_CHUNK_SEND(handle, cc_state, ev,
					      src_fsp, src_off,
					      dest_fsp, dest_off, num);
	if (tevent_req_nomem(subreq, req)) {
		return tevent_req_post(req, ev);
	}

	tevent_req_set_callback(subreq, bifrost_copy_chunk_done, req);
	return req;
}

static void bifrost_copy_chunk_done(struct tevent_req *subreq)
{
	struct tevent_req *req = tevent_req_callback_data(
		subreq, struct tevent_req);
	struct bifrost_cc_state *cc_state
			= tevent_req_data(req, struct bifrost_cc_state);
	NTSTATUS status;

	bifrost_log(__FUNCTION__);
	status = SMB_VFS_NEXT_COPY_CHUNK_RECV(cc_state->handle,
					      subreq,
					      &cc_state->copied);
	TALLOC_FREE(subreq);
	if (tevent_req_nterror(req, status)) {
		return;
	}
	tevent_req_done(req);
}

static NTSTATUS bifrost_copy_chunk_recv(struct vfs_handle_struct *handle,
				     struct tevent_req *req,
				     off_t *copied)
{
	struct bifrost_cc_state *cc_state
			= tevent_req_data(req, struct bifrost_cc_state);
	NTSTATUS status;
	bifrost_log(__FUNCTION__);

	*copied = cc_state->copied;
	if (tevent_req_is_nterror(req, &status)) {
		tevent_req_received(req);
		return status;
	}

	tevent_req_received(req);
	return NT_STATUS_OK;
}

static NTSTATUS bifrost_streaminfo(struct vfs_handle_struct *handle,
				struct files_struct *fsp,
				const char *fname,
				TALLOC_CTX *mem_ctx,
				unsigned int *num_streams,
				struct stream_struct **streams)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_STREAMINFO(handle,
				       fsp,
				       fname, mem_ctx, num_streams, streams);
}

static int bifrost_get_real_filename(struct vfs_handle_struct *handle,
				  const char *path,
				  const char *name,
				  TALLOC_CTX *mem_ctx, char **found_name)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GET_REAL_FILENAME(handle,
					      path, name, mem_ctx, found_name);
}

static const char *bifrost_connectpath(struct vfs_handle_struct *handle,
				    const char *filename)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CONNECTPATH(handle, filename);
}

static NTSTATUS bifrost_brl_lock_windows(struct vfs_handle_struct *handle,
				      struct byte_range_lock *br_lck,
				      struct lock_struct *plock,
				      bool blocking_lock,
				      struct blocking_lock_record *blr)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_BRL_LOCK_WINDOWS(handle,
					     br_lck, plock, blocking_lock, blr);
}

static bool bifrost_brl_unlock_windows(struct vfs_handle_struct *handle,
				    struct messaging_context *msg_ctx,
				    struct byte_range_lock *br_lck,
				    const struct lock_struct *plock)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_BRL_UNLOCK_WINDOWS(handle, msg_ctx, br_lck, plock);
}

static bool bifrost_brl_cancel_windows(struct vfs_handle_struct *handle,
				    struct byte_range_lock *br_lck,
				    struct lock_struct *plock,
				    struct blocking_lock_record *blr)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_BRL_CANCEL_WINDOWS(handle, br_lck, plock, blr);
}

static bool bifrost_strict_lock(struct vfs_handle_struct *handle,
			     struct files_struct *fsp,
			     struct lock_struct *plock)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_STRICT_LOCK(handle, fsp, plock);
}

static void bifrost_strict_unlock(struct vfs_handle_struct *handle,
			       struct files_struct *fsp,
			       struct lock_struct *plock)
{
	bifrost_log(__FUNCTION__);
	SMB_VFS_NEXT_STRICT_UNLOCK(handle, fsp, plock);
}

static NTSTATUS bifrost_translate_name(struct vfs_handle_struct *handle,
				    const char *mapped_name,
				    enum vfs_translate_direction direction,
				    TALLOC_CTX *mem_ctx, char **pmapped_name)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_TRANSLATE_NAME(handle, mapped_name, direction,
					   mem_ctx, pmapped_name);
}

static NTSTATUS bifrost_fsctl(struct vfs_handle_struct *handle,
			   struct files_struct *fsp,
			   TALLOC_CTX *ctx,
			   uint32_t function,
			   uint16_t req_flags,	/* Needed for UNICODE ... */
			   const uint8_t *_in_data,
			   uint32_t in_len,
			   uint8_t ** _out_data,
			   uint32_t max_out_len, uint32_t *out_len)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FSCTL(handle,
				  fsp,
				  ctx,
				  function,
				  req_flags,
				  _in_data,
				  in_len, _out_data, max_out_len, out_len);
}

static NTSTATUS bifrost_fget_nt_acl(vfs_handle_struct *handle, files_struct *fsp,
				 uint32 security_info,
				 TALLOC_CTX *mem_ctx,
				 struct security_descriptor **ppdesc)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FGET_NT_ACL(handle, fsp, security_info, mem_ctx,
					ppdesc);
}

static NTSTATUS bifrost_get_nt_acl(vfs_handle_struct *handle,
				const char *name, uint32 security_info,
				TALLOC_CTX *mem_ctx,
				struct security_descriptor **ppdesc)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GET_NT_ACL(handle, name, security_info, mem_ctx,
				       ppdesc);
}

static NTSTATUS bifrost_fset_nt_acl(vfs_handle_struct *handle, files_struct *fsp,
				 uint32 security_info_sent,
				 const struct security_descriptor *psd)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FSET_NT_ACL(handle, fsp, security_info_sent, psd);
}

static int bifrost_chmod_acl(vfs_handle_struct *handle, const char *name,
			  mode_t mode)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_CHMOD_ACL(handle, name, mode);
}

static int bifrost_fchmod_acl(vfs_handle_struct *handle, files_struct *fsp,
			   mode_t mode)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FCHMOD_ACL(handle, fsp, mode);
}

static SMB_ACL_T bifrost_sys_acl_get_file(vfs_handle_struct *handle,
				       const char *path_p,
				       SMB_ACL_TYPE_T type,
				       TALLOC_CTX *mem_ctx)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_GET_FILE(handle, path_p, type, mem_ctx);
}

static SMB_ACL_T bifrost_sys_acl_get_fd(vfs_handle_struct *handle,
				     files_struct *fsp, TALLOC_CTX *mem_ctx)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_GET_FD(handle, fsp, mem_ctx);
}

static int bifrost_sys_acl_blob_get_file(vfs_handle_struct *handle,
				      const char *path_p, TALLOC_CTX *mem_ctx,
				      char **blob_description, DATA_BLOB *blob)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_BLOB_GET_FILE(handle, path_p, mem_ctx,
						  blob_description, blob);
}

static int bifrost_sys_acl_blob_get_fd(vfs_handle_struct *handle,
				    files_struct *fsp, TALLOC_CTX *mem_ctx,
				    char **blob_description, DATA_BLOB *blob)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_BLOB_GET_FD(handle, fsp, mem_ctx,
						blob_description, blob);
}

static int bifrost_sys_acl_set_file(vfs_handle_struct *handle, const char *name,
				 SMB_ACL_TYPE_T acltype, SMB_ACL_T theacl)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_SET_FILE(handle, name, acltype, theacl);
}

static int bifrost_sys_acl_set_fd(vfs_handle_struct *handle, files_struct *fsp,
			       SMB_ACL_T theacl)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_SET_FD(handle, fsp, theacl);
}

static int bifrost_sys_acl_delete_def_file(vfs_handle_struct *handle,
					const char *path)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SYS_ACL_DELETE_DEF_FILE(handle, path);
}

static ssize_t bifrost_getxattr(vfs_handle_struct *handle, const char *path,
			     const char *name, void *value, size_t size)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_GETXATTR(handle, path, name, value, size);
}

static ssize_t bifrost_fgetxattr(vfs_handle_struct *handle,
			      struct files_struct *fsp, const char *name,
			      void *value, size_t size)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FGETXATTR(handle, fsp, name, value, size);
}

static ssize_t bifrost_listxattr(vfs_handle_struct *handle, const char *path,
			      char *list, size_t size)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_LISTXATTR(handle, path, list, size);
}

static ssize_t bifrost_flistxattr(vfs_handle_struct *handle,
			       struct files_struct *fsp, char *list,
			       size_t size)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FLISTXATTR(handle, fsp, list, size);
}

static int bifrost_removexattr(vfs_handle_struct *handle, const char *path,
			    const char *name)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_REMOVEXATTR(handle, path, name);
}

static int bifrost_fremovexattr(vfs_handle_struct *handle,
			     struct files_struct *fsp, const char *name)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FREMOVEXATTR(handle, fsp, name);
}

static int bifrost_setxattr(vfs_handle_struct *handle, const char *path,
			 const char *name, const void *value, size_t size,
			 int flags)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SETXATTR(handle, path, name, value, size, flags);
}

static int bifrost_fsetxattr(vfs_handle_struct *handle, struct files_struct *fsp,
			  const char *name, const void *value, size_t size,
			  int flags)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_FSETXATTR(handle, fsp, name, value, size, flags);
}

static bool bifrost_aio_force(struct vfs_handle_struct *handle,
			   struct files_struct *fsp)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_AIO_FORCE(handle, fsp);
}

static bool bifrost_is_offline(struct vfs_handle_struct *handle,
			    const struct smb_filename *fname,
			    SMB_STRUCT_STAT *sbuf)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_IS_OFFLINE(handle, fname, sbuf);
}

static int bifrost_set_offline(struct vfs_handle_struct *handle,
			    const struct smb_filename *fname)
{
	bifrost_log(__FUNCTION__);
	return SMB_VFS_NEXT_SET_OFFLINE(handle, fname);
}

/* VFS operations structure */

struct vfs_fn_pointers bifrost_fns = {
	/* Disk operations */

	.connect_fn = bifrost_connect,
	.disconnect_fn = bifrost_disconnect,
	.disk_free_fn = bifrost_disk_free,
	.get_quota_fn = bifrost_get_quota,
	.set_quota_fn = bifrost_set_quota,
	.get_shadow_copy_data_fn = bifrost_get_shadow_copy_data,
	.statvfs_fn = bifrost_statvfs,
	.fs_capabilities_fn = bifrost_fs_capabilities,
	.get_dfs_referrals_fn = bifrost_get_dfs_referrals,

	/* Directory operations */

	.opendir_fn = bifrost_opendir,
	.fdopendir_fn = bifrost_fdopendir,
	.readdir_fn = bifrost_readdir,
	.seekdir_fn = bifrost_seekdir,
	.telldir_fn = bifrost_telldir,
	.rewind_dir_fn = bifrost_rewind_dir,
	.mkdir_fn = bifrost_mkdir,
	.rmdir_fn = bifrost_rmdir,
	.closedir_fn = bifrost_closedir,
	.init_search_op_fn = vfs_bifrost_init_search_op,

	/* File operations */

	.open_fn = bifrost_open,
	.create_file_fn = bifrost_create_file,
	.close_fn = bifrost_close_fn,
	.read_fn = bifrost_vfs_read,
	.pread_fn = bifrost_pread,
	.pread_send_fn = bifrost_pread_send,
	.pread_recv_fn = bifrost_pread_recv,
	.write_fn = bifrost_write,
	.pwrite_fn = bifrost_pwrite,
	.pwrite_send_fn = bifrost_pwrite_send,
	.pwrite_recv_fn = bifrost_pwrite_recv,
	.lseek_fn = bifrost_lseek,
	.sendfile_fn = bifrost_sendfile,
	.recvfile_fn = bifrost_recvfile,
	.rename_fn = bifrost_rename,
	.fsync_fn = bifrost_fsync,
	.fsync_send_fn = bifrost_fsync_send,
	.fsync_recv_fn = bifrost_fsync_recv,
	.stat_fn = bifrost_stat,
	.fstat_fn = bifrost_fstat,
	.lstat_fn = bifrost_lstat,
	.get_alloc_size_fn = bifrost_get_alloc_size,
	.unlink_fn = bifrost_unlink,
	.chmod_fn = bifrost_chmod,
	.fchmod_fn = bifrost_fchmod,
	.chown_fn = bifrost_chown,
	.fchown_fn = bifrost_fchown,
	.lchown_fn = bifrost_lchown,
	.chdir_fn = bifrost_chdir,
	.getwd_fn = bifrost_getwd,
	.ntimes_fn = bifrost_ntimes,
	.ftruncate_fn = bifrost_ftruncate,
	.fallocate_fn = bifrost_fallocate,
	.lock_fn = bifrost_lock,
	.kernel_flock_fn = bifrost_kernel_flock,
	.linux_setlease_fn = bifrost_linux_setlease,
	.getlock_fn = bifrost_getlock,
	.symlink_fn = bifrost_symlink,
	.readlink_fn = bifrost_vfs_readlink,
	.link_fn = bifrost_link,
	.mknod_fn = bifrost_mknod,
	.realpath_fn = bifrost_realpath,
	.notify_watch_fn = bifrost_notify_watch,
	.chflags_fn = bifrost_chflags,
	.file_id_create_fn = bifrost_file_id_create,
	.copy_chunk_send_fn = bifrost_copy_chunk_send,
	.copy_chunk_recv_fn = bifrost_copy_chunk_recv,

	.streaminfo_fn = bifrost_streaminfo,
	.get_real_filename_fn = bifrost_get_real_filename,
	.connectpath_fn = bifrost_connectpath,
	.brl_lock_windows_fn = bifrost_brl_lock_windows,
	.brl_unlock_windows_fn = bifrost_brl_unlock_windows,
	.brl_cancel_windows_fn = bifrost_brl_cancel_windows,
	.strict_lock_fn = bifrost_strict_lock,
	.strict_unlock_fn = bifrost_strict_unlock,
	.translate_name_fn = bifrost_translate_name,
	.fsctl_fn = bifrost_fsctl,

	/* NT ACL operations. */

	.fget_nt_acl_fn = bifrost_fget_nt_acl,
	.get_nt_acl_fn = bifrost_get_nt_acl,
	.fset_nt_acl_fn = bifrost_fset_nt_acl,

	/* POSIX ACL operations. */

	.chmod_acl_fn = bifrost_chmod_acl,
	.fchmod_acl_fn = bifrost_fchmod_acl,

	.sys_acl_get_file_fn = bifrost_sys_acl_get_file,
	.sys_acl_get_fd_fn = bifrost_sys_acl_get_fd,
	.sys_acl_blob_get_file_fn = bifrost_sys_acl_blob_get_file,
	.sys_acl_blob_get_fd_fn = bifrost_sys_acl_blob_get_fd,
	.sys_acl_set_file_fn = bifrost_sys_acl_set_file,
	.sys_acl_set_fd_fn = bifrost_sys_acl_set_fd,
	.sys_acl_delete_def_file_fn = bifrost_sys_acl_delete_def_file,

	/* EA operations. */
	.getxattr_fn = bifrost_getxattr,
	.fgetxattr_fn = bifrost_fgetxattr,
	.listxattr_fn = bifrost_listxattr,
	.flistxattr_fn = bifrost_flistxattr,
	.removexattr_fn = bifrost_removexattr,
	.fremovexattr_fn = bifrost_fremovexattr,
	.setxattr_fn = bifrost_setxattr,
	.fsetxattr_fn = bifrost_fsetxattr,

	/* aio operations */
	.aio_force_fn = bifrost_aio_force,

	/* offline operations */
	.is_offline_fn = bifrost_is_offline,
	.set_offline_fn = bifrost_set_offline
};

NTSTATUS vfs_bifrost_init(void);
NTSTATUS vfs_bifrost_init(void)
{
	return smb_register_vfs(SMB_VFS_INTERFACE_VERSION, "bifrost",
				&bifrost_fns);
}
