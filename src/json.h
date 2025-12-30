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

enum json_bool
{
	FALSE,
	TRUE
};

enum json_bool json_character_is_whitespace(char ascii);
enum json_bool json_character_is_digit(char ascii);
enum json_bool json_character_is_hex(char ascii);
enum json_bool json_character_is_control(char ascii);

char * json_whitespace(char *json_start, char *json_end);
char * json_string(char *json_start, char *json_end);
char * json_number(char *json_start, char *json_end);
char * json_object_start(char *json_start, char *json_end);
char * json_object_key(char *json_start, char *json_end);
char * json_object_end(char *json_start, char *json_end);
char * json_array_start(char *json_start, char *json_end);
char * json_array_end(char *json_start, char *json_end);
char * json_true(char *json_start, char *json_end);
char * json_false(char *json_start, char *json_end);
char * json_null(char *json_start, char *json_end);
char * json_next(char *json_start, char *json_end);

