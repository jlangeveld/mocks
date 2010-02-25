# If environment variable $TERM is empty, no terminal is present and therefore no colors should be used
ifeq ($(TERM),)
	l=\n #normal
	c=\n #normal
	i=\n #normal
	e=\n #normal
else
	l=[01;36;01m\n #cyan
	c=[01;32;01m\n #green
	i=[01;35;01m\n #magenta
	e=[m\n #normal
endif