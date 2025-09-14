CFLAGS = -Wall -Wextra -WPedantic

normal: release

cosmic-monkey: stencil/cosmic_monkey.c 
	cc $(CFLAGS) stencil/cosmic_monkey.c -o build/cosmic-monkey

release: CFLAGS += -O2
release: cosmic-monkey

debug: CFLAGS += -O0 -DDEBUG
debug: cosmic-monkey
