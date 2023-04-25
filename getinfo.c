#include "custom_shell.h"

/**
 * clear_custom_info - initializes custom_info_t struct
 * @info: struct address
 */
void clear_custom_info(custom_info_t *info)
{
    info->arg = NULL;
    info->argv = NULL;
    info->path = NULL;
    info->argc = 0;
}

/**
 * set_custom_info - initializes custom_info_t struct
 * @info: struct address
 * @av: argument vector
 */
void set_custom_info(custom_info_t *info, char **av)
{
    int i = 0;

    info->fname = av[0];
    if (info->arg)
    {
        info->argv = custom_strtow(info->arg, " \t");
        if (!info->argv)
        {

            info->argv = malloc(sizeof(char *) * 2);
            if (info->argv)
            {
                info->argv[0] = custom_strdup(info->arg);
                info->argv[1] = NULL;
            }
        }
        for (i = 0; info->argv && info->argv[i]; i++)
            ;
        info->argc = i;

        replace_custom_alias(info);
        replace_custom_vars(info);
    }
}

/**
 * free_custom_info - frees custom_info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_custom_info(custom_info_t *info, int all)
{
    custom_ffree(info->argv);
    info->argv = NULL;
    info->path = NULL;
    if (all)
    {
        if (!info->cmd_buf)
            free(info->arg);
        if (info->custom_env)
            free_custom_list(&(info->custom_env));
        if (info->history)
            free_custom_list(&(info->history));
        if (info->custom_alias)
            free_custom_list(&(info->custom_alias));
        custom_ffree(info->custom_environ);
        info->custom_environ = NULL;
        custom_bfree((void **)info->cmd_buf);
        if (info->readfd > 2)
            close(info->readfd);
        custom_putchar(BUF_FLUSH);
    }
}
