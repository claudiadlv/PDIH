/**
 * @file miejemplo.c
 * @author Claudia de la Vieja Lafuente
 * @date 3 de junio de 2024
 * @version 0.1
 * @brief An introductory loadable kernel module (LKM).
 */

#include <linux/module.h>
#include <linux/kernel.h>

int init_module(void) {
    printk(KERN_INFO "Hola, mundo desde el kernel!\n");
    return 0;  // 0 significa que está todo bien, cualquier otro valor indica error
}

void cleanup_module(void) {
    printk(KERN_INFO "Adiós, mundo desde el kernel!\n");
}

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Un módulo sencillo de ejemplo");
MODULE_AUTHOR("Claudia de la Vieja");
