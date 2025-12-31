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

/**
 * @brief A simple boolean implementation.
 */
enum json_bool
{
	FALSE,
	TRUE
};

/**
 * @brief Check whether a character is a valid whitespace character.
 * @param ascii ascii character
 * @return TRUE if whitespace, otherwise FALSE
 */
enum json_bool json_character_is_whitespace(char ascii);

/**
 * @brief Check whether a character is a valid digit.
 * @param ascii ascii character
 * @return TRUE if digit, otherwise FALSE
 */
enum json_bool json_character_is_digit(char ascii);

/**
 * @brief Check whether a character is a valid hex digit.
 * @param ascii ascii character
 * @return TRUE if hex, otherwise FALSE
 */
enum json_bool json_character_is_hex(char ascii);

/**
 * @brief Check whether a character is a valid control character.
 * @param ascii ascii character
 * @Return TRUE if control, otherwise FALSE
 */
enum json_bool json_character_is_control(char ascii);

/**
 * @brief Consume whitespace until the first non-whitespace character. 
 * NULL may indicate invalid pointer arguments, or that the string is entirely whitespace.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first non-whitespace character
 */
char * json_whitespace(char *json_start, char *json_end);

/**
 * @brief Consume a string.
 * NULL may indicate invalid pointer arguments, or that a string wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the string
 */
char * json_string(char *json_start, char *json_end);

/**
 * @brief Consume a number.
 * NULL may indicate invalid pointer arguments, or that a number wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the number
 */
char * json_number(char *json_start, char *json_end);

/**
 * @brief Consume an object start ('{').
 * NULL may indicate invalid pointer arguments, or that an object start wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the object start
 */
char * json_object_start(char *json_start, char *json_end);

/**
 * @brief Consume an object key (json_string + ':').
 * NULL may indicate invalid pointer arguments, or than an object key wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the object key
 */
char * json_object_key(char *json_start, char *json_end);

/**
 * @brief Consume an object end ('}').
 * NULL may indicate invalid pointer arguments, or that an object end wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the object end
 */
char * json_object_end(char *json_start, char *json_end);

/**
 * @brief Consume an array start ('[').
 * NULL may indicate invalid pointer arguments, or that an array start wasn't the next token.
 * 
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the array start
 */ 
char * json_array_start(char *json_start, char *json_end);

/**
 * @brief Consume an array end (']').
 * NULL may indicate invalid pointer arguments, or that an array end wasn't the next token.
 * 
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the array end
 */ 
char * json_array_end(char *json_start, char *json_end);

/**
 * @brief Consume a true literal.
 * NULL may indicate invalid pointer arguments, or that a true literal wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the true literal
 */
char * json_true(char *json_start, char *json_end);

/**
 * @brief Consume a false literal.
 * NULL may indicate invalid pointer arguments, or that a false literal wasn't the next token.
 * 
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the false literal
 */
char * json_false(char *json_start, char *json_end);

/**
 * @brief Consume a null literal.
 * NULL may indicate invalid pointer arguments, or that a null literal wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the null literal
 */
char * json_null(char *json_start, char *json_end);

/**
 * @brief Consume a ','.
 * NULL may indicate invalid pointer arguments, or that a ',' wasn't the next token.
 *
 * @param json_start parsing starts at this character
 * @param json_end parsing stops before this character
 * @return NULL if invalid, otherwise the first character after the ','
 */
char * json_next(char *json_start, char *json_end);

