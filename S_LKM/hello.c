/**
 * @file hello.c
 * @author Derek Molloy
 * @date 4 April 2015
 * @version 0.1
 * @brief An introductory loadable kernel module (LKM).
 * @see http://www.derekmolloy.ie/ for a full description
 */
#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
MODULE_LICENSE("GPL"); ///< The license type
MODULE_AUTHOR("Derek Molloy"); ///< The author
MODULE_DESCRIPTION("A simple Linux driver."); ///< description
MODULE_VERSION("0.1"); ///< The version of the module
static char *name = "world";
module_param(name, charp, S_IRUGO);
MODULE_PARM_DESC(name, "The name to display in log");
/** @brief The LKM initialization function
* @return returns 0 if successful
*/
static int __init helloBBB_init(void){
 printk(KERN_INFO "EBB: Hello %s from the BBB LKM!\n", name);
 return 0;
}
/** @brief The LKM cleanup function
*/
static void __exit helloBBB_exit(void){
 printk(KERN_INFO "EBB: Goodbye %s from BBB LKM!\n", name);
}
/** @brief Identify the initialization function at insertion
time and the cleanup function
*/
module_init(helloBBB_init);
module_exit(helloBBB_exit);
