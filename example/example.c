#include "json.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void print(char *start, char *end)
{
	// sanity check pointers: they could still reference bad memory, but that's on the user

	if(start == NULL || end == NULL || start >= end)
	{
		assert(0);
	}

	for(char *string = start; string < end; string++)
	{
		printf("%c", *string);
	}
}

int main(int argc, char *argv[])
{
	char *json_start = "{\"a\": \"abc\", \"b\": 123.456e+789, \"c\": {\"d\": [true, false, null]}}";
	char *json_end = json_start + strlen(json_start);
	
	// all json parsing methods return the first character AFTER the value

	char *key_start = json_object_start(json_start, json_end); // this returns the first char after '{'; which should be a key, hence key_start
	char *value_start = json_object_key(key_start, json_end); // this returns the first char after ':'; which should be a value, hence value_start

	// error-checking is provided here as an example, and will be omitted in the rest of the program
	// despite this, error-checking should ALWAYS be done	

	// if key_start is null, then json_object_start failed; '{' was NOT the next token
	// if value_start is null, then json_object_key failed; an object key was NOT the next token

	if(key_start == NULL || value_start == NULL)
	{
		assert(!"Invalid JSON!");
	}

	printf("key: ");
	print(key_start, json_string(key_start, value_start));
	printf(" ");

	char *value_end = json_string(value_start, json_end);

	// you can use json_whitespace to strip whitespace

	printf("value: ");
	print(json_whitespace(value_start, value_end), value_end);
	printf(", ");

	key_start = json_next(value_end, json_end);
	value_start = json_object_key(key_start, json_end);

	printf("key: ");
	print(key_start, json_string(key_start, value_start));
	printf(" ");

	value_end = json_number(value_start, json_end);

	printf("value: ");
	print(value_start, value_end);
	printf(", ");

	key_start = json_next(value_end, json_end);
	value_start = json_object_key(key_start, json_end);

	printf("key: ");
	print(key_start, json_string(key_start, value_start));
	printf(" ");

	key_start = json_object_start(value_start, json_end);
	printf("value: { ");

	value_start = json_object_key(key_start, json_end);

	printf("key: ");
	print(key_start, json_string(key_start, value_start));
	printf(" ");
	
	char *array_start = json_array_start(value_start, json_end);
	printf("value: [ ");

	value_end = json_true(array_start, json_end);

	printf("value: ");
	print(array_start, value_end);
	printf(", ");

	array_start = json_next(value_end, json_end);
	value_end = json_false(array_start, json_end);

	printf("value: ");
	print(array_start, value_end);
	printf(", ");

	array_start = json_next(value_end, json_end);
	value_end = json_null(array_start, json_end);

	printf("value: ");
	print(array_start, value_end);

	value_end = json_array_end(value_end, json_end);
	printf(" ]");

	value_end = json_object_end(value_end, json_end);
	printf(" }");	
	
	value_end = json_object_end(value_end, json_end);
	printf(" }\n");

	return 0;
}
