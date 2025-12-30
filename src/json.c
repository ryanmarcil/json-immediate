/* Copyright 2025 Ryan S. Marcil 
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "json.h"

#ifndef NULL
#define NULL ((void *) 0)
#endif

enum json_bool json_character_is_whitespace(char ascii)
{
	switch(ascii)
	{
		case ' ':
		case '\n':
		case '\r':
		case '\t':
			return TRUE;
		default:
			return FALSE;
	}
}

enum json_bool json_character_is_digit(char ascii)
{
	return ('0' <= ascii && ascii <= '9') ? TRUE : FALSE;
}

enum json_bool json_character_is_hex(char ascii)
{
	return (('0' <= ascii && ascii <= '9') || ('A' <= ascii && ascii <= 'F')) ? TRUE : FALSE;
}

enum json_bool json_character_is_control(char ascii)
{
	return ((0 <= ascii && ascii <= 31) || (ascii == 127)) ? TRUE : FALSE;
}

char * json_whitespace(char *json_start, char *json_end)
{
	if(json_start == NULL || json_end == NULL || json_start >= json_end)
	{
		return NULL;
	}

	for( ; json_start < json_end; json_start++)
	{
		if(json_character_is_whitespace(*json_start) == FALSE)
		{
			return json_start;
		}
	}

	return NULL;
}

char * json_string(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start != '"')
	{
		return NULL;
	}

	json_start += 1;
	
	for( ; json_start < json_end; json_start++)
	{
		if(*json_start == '"')
		{
			json_start += 1;
			return json_start;
		}

		if(*json_start == '\\')
		{
			json_start += 1;

			if(json_start >= json_end)
			{
				return NULL;
			}	

			switch(*json_start)
			{
				case '"':
				case '\\':
				case '/':
				case 'b':
				case 'f':
				case 'n':
				case 'r':
				case 't':
					break;

				case 'u':
					json_start += 1;

					for(int i = 0; i < 4 && json_start < json_end; i++, json_start++)
					{
						if(json_character_is_hex(*json_start) == FALSE)
						{
							return NULL;
						}
					}	

					break;	

				default:
					return NULL;
			}

			continue;
		}

		if(json_character_is_control(*json_start) == TRUE)
		{
			return NULL;
		}
	}

	return NULL;	
}

char * json_number(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == '-')
	{
		json_start += 1;

		if(json_start >= json_end || json_character_is_digit(*json_start) == FALSE)
		{
			return NULL;
		}
	}

	if(*json_start == '0')
	{
		json_start += 1;

		if(json_start >= json_end)
		{
			return json_start;
		}	

		if(json_character_is_digit(*json_start) == TRUE)
		{
			return NULL;
		}
	}
	else if(json_character_is_digit(*json_start) == FALSE)
	{
		return NULL;
	}

	for( ; json_start < json_end; json_start++)
	{
		if(json_character_is_digit(*json_start) == FALSE)
		{
			break;
		}
	}

	if(*json_start == '.')
	{
		json_start += 1;

		if(json_start >= json_end || json_character_is_digit(*json_start) == FALSE)
		{
			return NULL;
		}	

		for( ; json_start < json_end; json_start++)
		{
			if(json_character_is_digit(*json_start) == FALSE)
			{
				break;
			}
		}
	}

	if(*json_start == 'E' || *json_start == 'e')
	{
		json_start += 1;

		if(json_start >= json_end)
		{
			return NULL;
		}

		if(*json_start == '+' || *json_start == '-')
		{
			json_start += 1;
		}

		if(json_start >= json_end || json_character_is_digit(*json_start) == FALSE)
		{
			return NULL;
		}

		for( ; json_start < json_end; json_start++)
		{
			if(json_character_is_digit(*json_start) == FALSE)
			{
				break;
			}
		}
	}

	return json_start;	
}

char * json_object_start(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == '{')
	{
		json_start += 1;
		return json_start;
	}
	
	return NULL;
}

char * json_object_key(char *json_start, char *json_end)
{
	if((json_start = json_string(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == ':')
	{
		json_start += 1;
		return json_start;
	}

	return NULL;
}

char * json_object_end(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == '}')
	{
		json_start += 1;
		return json_start;
	}	

	return NULL;
}

char * json_array_start(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == '[')
	{
		json_start += 1;
		return json_start;
	}

	return NULL;
}

char * json_array_end(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == ']')
	{
		json_start += 1;
		return json_start;
	}

	return NULL;
}

char * json_true(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	static char json_true[] = {'t', 'r', 'u', 'e'};
	
	for(int i = 0; i < sizeof(json_true) && json_start < json_end; i++, json_start++)
	{
		if(*json_start != json_true[i])
		{
			return NULL;
		}	
	}

	return json_start;
}

char * json_false(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	static char json_false[] = {'f', 'a', 'l', 's', 'e'};
	
	for(int i = 0; i < sizeof(json_false) && json_start < json_end; i++, json_start++)
	{
		if(*json_start != json_false[i])
		{
			return NULL;
		}
	}

	return json_start;
}

char * json_null(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	static char json_null[] = {'n', 'u', 'l', 'l'};

	for(int i = 0; i < sizeof(json_null) && json_start < json_end; i++, json_start++)
	{
		if(*json_start != json_null[i])
		{
			return NULL;
		}
	}

	return json_start;
}

char * json_next(char *json_start, char *json_end)
{
	if((json_start = json_whitespace(json_start, json_end)) == NULL)
	{
		return NULL;
	}

	if(*json_start == ',')
	{
		json_start += 1;
		return json_start;
	}

	return NULL;
}

