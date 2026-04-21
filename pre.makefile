MODEL_CONVERTER = ../../../ModelConverter/ModelConverter.exe
ASSET_OBJ_DIR = assets/obj
ASSET_NYA_DIR = cd/data

MODELS_OBJ_P = $(shell find $(ASSET_MODELS_DIR) -name '*.obj')
MODELS_OBJ := $(patsubst %.obj,%.obj,$(notdir $(MODELS_OBJ_P)))
MODELS_NYA = $(MODELS_OBJ:%.obj=%.NYA)
$(info ****** pre makefile ******)


%.NYA : %.obj
	$(info converting $< into $@)
	$(MODEL_CONVERTER) -i "$(ASSET_OBJ_DIR)/$<" -o "$(ASSET_NYA_DIR)/$@"

pre_build: $(MODELS_NYA)
	$(info ****** pre build step ******)
	$(info $(MODELS_OBJ))



