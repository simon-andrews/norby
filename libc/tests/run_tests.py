import os
import sys

use_verbose_logging = 'verbose' in sys.argv

def sh(cmd):
	if use_verbose_logging:
		print(cmd)
	return os.system(cmd)

def compile_test(test):
	sh('gcc -std=gnu99 -Wall -Wextra -I../include -ffreestanding -nostdlib -c {test}.c -o {test}.o'.format(test=test))

def link_test(test):
	sh('ld main.o {test}.o ../../build/libc_host/libnorbyc.a -o {test}.bin'.format(test=test))

def run_test(test):
	print('{test}... '.format(test=test), end='')
	return os.system('./{test}.bin'.format(test=test))

def cleanup_after_test(test):
	for extension in ['.o', '.bin']:
		os.remove(test + extension)

tests = [item[:-2] for item in os.listdir('.') if item.endswith('.c') and os.path.isfile(item)]

print('\033[1m+-------------------------------------+')
print(       '| Starting Norby C Library Test Suite |')
print(       '+-------------------------------------+\033[0m')
sh('nasm main.asm -felf64 -o main.o')

failure_count = 0
for test in tests:
	compile_test(test)
	link_test(test)
	if run_test(test) != 0:
		failure_count += 1
		print('\033[91mFAILURE!\033[0m')
	else:
		print('\033[92mSUCCESS!\033[0m')
	cleanup_after_test(test)

exit(failure_count)
