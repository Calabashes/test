#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/kobject.h>

volatile int aa = 0;

struct my_kobj {	
	int val;
	struct kobject kobj;
};

struct my_kobj *obj1, *obj2;
struct my_kobj obj3;
//memset(&obj3, 0, sizeof(stuct my_kobj));
//struct bin_attribute bin_attri;
//memset(&bin_attri, 0, sizeof(struct bin_attribute);


static int bin_show(struct file *filp, struct kobject *kobj,struct bin_attribute *bin_attr, char *buf, loff_t offset, size_t count)
{
	printk("Line :%d, Fun:%s\n",__LINE__,__FUNCTION__);

	return 0;
}


static int  bin_store(struct file *filp, struct kobject *kobj, struct bin_attribute *bin_attr, char *buf, loff_t offset, size_t count)
{
	printk("Line:%d, Fun:%s\n",__LINE__,__FUNCTION__);

	return 0;
	
}



static struct bin_attribute bin_attri = {
	.attr = {
		.name = "bin_attr",
		.mode = S_IRUSR,
	},
	.size = 0,
	.read = bin_show,
	.write = bin_store
};




struct kobj_type my_type;

struct attribute name_attr = {
	.name = "name",
	.mode = 0444,
};

struct attribute val_attr = {
	.name = "val",
	.mode = 0666,
};

struct attribute length_attr = {
	.name = "length",
	.mode = 0666,
};

struct attribute *my_attrs[] = {
	&name_attr,
	&val_attr,
	NULL,
};

ssize_t my_show(struct kobject *kobj, struct attribute *attr, char *buffer)
{
	struct my_kobj *obj = container_of(kobj, struct my_kobj, kobj);

	ssize_t count = 0;


	printk("aa = %d\n",aa);

	aa++;

	if(strcmp(attr->name, "name") == 0) {
		count = sprintf(buffer, "%s\n",kobject_name(kobj));
	}else if(strcmp(attr->name, "val") == 0) {
		count = sprintf(buffer, "%d\n",obj->val);
	}

	return count;

}

ssize_t my_store(struct kobject *kobj, struct attribute *attr, const char* buffer, size_t size)
{
	struct my_kobj *obj = container_of(kobj, struct my_kobj, kobj);

	if(strcmp(attr->name, "val") == 0) {
		sscanf(buffer, "%d", &obj->val);
	}

	

	return size;

}

struct sysfs_ops my_sysfsops = {
	.show = my_show,
	.store = my_store,
};

void obj_release(struct kobject *kobj)
{
	struct my_kobj *obj = container_of(kobj, struct my_kobj, kobj);

	printk("obj release %s\n",kobject_name(&obj->kobj));

	kfree(obj);

}

static int __init mykobj_init(void)
{
	printk("kboj init\n");
	int ret = 0;

	obj1 = kzalloc(sizeof(struct my_kobj),GFP_KERNEL);
	obj2 = kzalloc(sizeof(struct my_kobj), GFP_KERNEL);

	obj2->val = 2;

	my_type.release = obj_release;
	my_type.default_attrs = my_attrs;
	my_type.sysfs_ops = &my_sysfsops;

	kobject_init_and_add(&obj1->kobj, &my_type, NULL, "mykobj1");
	kobject_init_and_add(&obj2->kobj, &my_type, &obj1->kobj, "mykobj2");
	kobject_init_and_add(&obj3.kobj, &my_type, &obj2->kobj, "mykobj3");

	
	ret = sysfs_create_file(&obj1->kobj, &length_attr);
	ret = sysfs_create_bin_file(&obj1->kobj, &bin_attri);
	ret = sysfs_create_link(&obj1->kobj, &obj3.kobj,"link_file");

	return ret;

}

static void __exit mykobj_exit(void)
{
	printk("my kobj exit\n");

	int ret;
	sysfs_remove_bin_file(&(obj1->kobj), &bin_attri);
	sysfs_remove_link(&(obj1->kobj),kobject_name(&obj3.kobj));

	kobject_del(&obj2->kobj);
	kobject_put(&obj2->kobj);

	kobject_del(&obj1->kobj);
	kobject_put(&obj1->kobj);



	return;

}

module_init(mykobj_init);
module_exit(mykobj_exit);

MODULE_LICENSE("GPL");
