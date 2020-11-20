#include <linux/fs.h>
#include <linux/init.h>
#include <linux/module.h>
#include "phat32.h"

static struct file_system_type phat32_type = {
  .owner = THIS_MODULE,
  .name = "phat32",
  .mount = phat32_mount,
  .kill_sb = kill_block_super,
  .fs_flags = FS_REQUIRES_DEV,
};

static int __init phat32_init(void) {
  pr_debug("phat32 module loaded\n");
  register_filesystem(&phat32_type);
  return 0;
}

static void __exit phat32_exit(void) {
  pr_debug("phat32 module unloaded\n");
}

module_init(phat32_init);
module_exit(phat32_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("stbenjam");

static int phat32_fill_sb(struct super_block *sb, void *data, int silent) {
  return 0;
}

static struct dentry *phat32_mount(struct file_system_type *type, int flags, char const *dev, void *data) {
  struct dentry *const entry = mount_bdev(type, flags, dev, data, phat32_fill_sb);

  if (IS_ERR(entry))
    pr_err("failed to mount phat32 fs\n");
  else
    pr_debug("phat32 fs mounted successfully");

  return entry;
}
