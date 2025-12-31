#include "json.h"
#include <stdio.h>
#include <assert.h>
#include <string.h>

void print(char *start, char *end)
{
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

	char *key_start = json_object_start(json_start, json_end);
	assert(key_start != NULL);
	printf("{ ");

	char *value_start = json_object_key(key_start, json_end);
	assert(value_start != NULL);
	printf("KEY: ");
	print(json_whitespace(key_start, value_start), json_string(key_start, value_start));
	printf(" ");

	char *value_end = json_string(value_start, json_end);
	assert(value_end != NULL);
	printf("VALUE: ");
	print(json_whitespace(value_start, value_end), value_end);
	printf(", ");

	key_start = json_next(value_end, json_end);
	assert(key_start != NULL);

	value_start = json_object_key(key_start, json_end);
	assert(value_start != NULL);
	printf("KEY: ");
	print(json_whitespace(key_start, value_start), json_string(key_start, value_start));
	printf(" ");

	value_end = json_number(value_start, json_end);
	assert(value_end != NULL);	
	printf("VALUE: ");
	print(json_whitespace(value_start, value_end), value_end);
	printf(", ");

	key_start = json_next(value_end, json_end);
	assert(key_start != NULL);

	value_start = json_object_key(key_start, json_end);
	assert(value_start != NULL);
	printf("KEY: ");
	print(json_whitespace(key_start, value_start), json_string(key_start, value_start));
	printf(" ");

	key_start = json_object_start(value_start, json_end);
	assert(value_end != NULL);	
	printf("VALUE: { ");

	value_start = json_object_key(key_start, json_end);
	assert(key_start != NULL);
	printf("KEY: ");
	print(json_whitespace(key_start, value_start), json_string(key_start, value_start));
	printf(" ");
	
	char *array_start = json_array_start(value_start, json_end);
	assert(array_start != NULL);	
	printf("VALUE: [ ");

	value_end = json_true(array_start, json_end);
	assert(value_end != NULL);
	printf("VALUE: ");
	print(json_whitespace(array_start, value_end), value_end);
	printf(", ");

	array_start = json_next(value_end, json_end);
	assert(array_start != NULL);

	value_end = json_false(array_start, json_end);
	assert(value_end != NULL);
	printf("VALUE: ");
	print(json_whitespace(array_start, value_end), value_end);
	printf(", ");

	array_start = json_next(value_end, json_end);
	assert(array_start != NULL);

	value_end = json_null(array_start, json_end);
	assert(value_end != NULL);
	printf("VALUE: ");
	print(json_whitespace(array_start, value_end), value_end);

	value_end = json_array_end(value_end, json_end);
	assert(value_end != NULL);
	printf(" ]");

	value_end = json_object_end(value_end, json_end);
	assert(value_end != NULL);
	printf(" }");	
	
	value_end = json_object_end(value_end, json_end);
	assert(value_end != NULL);
	printf(" }\n");

	return 0;
}
