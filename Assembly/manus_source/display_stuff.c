#include "function_prototypes.h"
#include "ft_printf.h"

void display_token(t_token *token)
{
    char *type;
    char *argumnet_type;

    if (!token)
    {
        ft_printf("Null token\n");
        ft_printf("---------------\n");
        return ;
    }
    type = "unknown";
    if (token->type == command_name)
        type = "command_name";
    else if (token->type == command_comment)
        type = "command_comment";
    else if (token->type == string)
        type = "string";
    else if (token->type == label)
        type = "label";
    else if (token->type == operation)
        type = "operation";
    else if (token->type == argument)
        type = "argument";
    else if (token->type == comment)
        type = "comment";
    else if (token->type == new_line)
        type = "new_line";
    else if (token->type == opening_quotation_mark)
        type = "opening_quotation_mark";
    else if (token->type == closing_quotation_mark)
        type = "closing_quotation_mark";
    else if (token->type == hashtag)
        type = "hashtag";
    else if (token->type == comma)
        type = "comma";
    ft_printf("Token at %p\nString: %s\n", token, token->type == new_line ? "\\n" : token->string);
    ft_printf("type: %s\n", type);
    if (token->type == argument)
    {
        if (token->argument_type == registry)
            argumnet_type = "registry";
        else if (token->argument_type == direct)
            argumnet_type = "direct";
        else if (token->argument_type == indirect)
            argumnet_type = "indirect";
        else
            argumnet_type = "not_applicable";
        ft_printf("argument_type: %s\n", argumnet_type);
    }
    ft_printf("size: %d\n", token->size);
    ft_printf("distance: %d\n", token->distance);
    ft_printf("---------------\n");
}

void display_all_tokens(t_generic_list *tokens)
{
    t_generic_list *current;

    current = tokens;
    while (current != NULL)
    {
        display_token((t_token *)current->stuff);
        current = current->next;
    }
}

void display_classification_error_message(t_token *token, int verbose)
{
    if (verbose)
    {
        ft_printf(CLASSIFICATION_ERROR_MESSAGE);
        display_token(token);
    }
    else
    {
        ft_printf(GENERIC_ERROR_MESSAGE);
    }
    exit(1);
}

void invoke_error(char *error_message)
{
    ft_printf(error_message);
    exit(1);
}

void display_byte_strings(t_generic_list *tokens)
{
    t_generic_list *current;

    current = tokens;
    while (current)
    {
        ft_printf("%s", current->stuff);
        current = current->next;
    }
}

void string_to_bytes(char *string, int file_descriptor)
{
    int index;
    int length;
    char *current_byte;
    unsigned char byte_value;

    index = 0;
    length = ft_strlen(string);
    if (length == 0 || (length % 2) != 0)
        invoke_error("string is broken;"); //EMSG
    while (index < length)
    {
        current_byte = ft_strsub(string, index, 2); //leak;
        ft_dprintf(file_descriptor, "%c", ft_atoi_base(current_byte, NUMBER_SYSTEM_BASE));
        // ft_printf("%d ", ft_atoi_base(current_byte, NUMBER_SYSTEM_BASE));
        index = index + 2;
    }
}

void tokens_to_bytes(t_generic_list *tokens, int file_descriptor)
{
    t_generic_list *current_token;

    current_token = tokens;
    while(current_token)
    {
        string_to_bytes(current_token->stuff, file_descriptor);
        current_token = current_token->next;
    }
}

