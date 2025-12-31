# json-immediate
an immediate mode JSON parser. 

## build
json-immediate doesn't rely on libc:
- if NULL isn't defined, json-immediate uses its own definition

### example
<pre>
mkdir -p bin
gcc -Isrc src/*.c example/example.c -o bin/example && bin/example
gcc -Isrc src/*.c example/test.c -o bin/example test && bin/test
</pre>
