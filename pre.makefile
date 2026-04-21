SOURCESB = $(patsubst ./%,%,$(shell find src/ -name '*.c'))
pre_build:
	$(info ****** pre build step ******)
	$(info    VAR is $(SOURCESB))