#include "custom_shell.h"

/**
 * get_custom_environ - returns a copy of the string array for custom_environ
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
char **get_custom_environ(info_t *info)
{
    if (!info->custom_environ || info->env_changed)
    {
        info->custom_environ = list_to_strings(info->custom_env);
        info->env_changed = 0;
    }

    return (info->custom_environ);
}

/**
 * _custom_unsetenv - Remove an environment variable in custom_env
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _custom_unsetenv(info_t *info, char *var)
{
    list_t *node = info->custom_env;
    size_t i = 0;
    char *p;

    if (!node || !var)
        return (0);

    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            info->env_changed = delete_node_at_index(&(info->custom_env), i);
            i = 0;
            node = info->custom_env;
            continue;
        }
        node = node->next;
        i++;
    }
    return (info->env_changed);
}

/**
 * _custom_setenv - Initialize a new environment variable,
 *                  or modify an existing one in custom_env
 * @info: Structure containing potential arguments. Used to maintain
 *        constant function prototype.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
 */
int _custom_setenv(info_t *info, char *var, char *value)
{
    char *buf = NULL;
    list_t *node;
    char *p;

    if (!var || !value)
        return (0);

    buf = malloc(_strlen(var) + _strlen(value) + 2);
    if (!buf)
        return (1);
    _strcpy(buf, var);
    _strcat(buf, "=");
    _strcat(buf, value);
    node = info->custom_env;
    while (node)
    {
        p = starts_with(node->str, var);
        if (p && *p == '=')
        {
            free(node->str);
            node->str = buf;
            info->env_changed = 1;
            return (0);
        }
        node = node->next;
    }
    add_node_end(&(info->custom_env), buf, 0);
    free(buf);
    info->env_changed = 1;
    return (0);
}
