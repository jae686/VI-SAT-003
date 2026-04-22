MODEL_CONVERTER = ../../../ModelConverter/ModelConverter.exe
ASSET_OBJ_DIR = assets/obj
ASSET_NYA_DIR = cd/data

MODELS_OBJ_P = $(shell find $(ASSET_MODELS_DIR) -name '*.obj')
MODELS_OBJ := $(patsubst %.obj,%.obj,$(notdir $(MODELS_OBJ_P)))
MODELS_NYA = $(MODELS_OBJ:%.obj=%.NYA)
$(info ****** pre makefile ******)


pre_build: convert_models
	$(info ****** pre build step ******)
	$(info $(MODELS_OBJ))
	$(info $(MODELS_NYA))

convert_models: $(ASSET_NYA_DIR)/$(MODELS_NYA)

#%.NYA: %.obj
#	$(info converting__debug $< into $@)
#	$(MODEL_CONVERTER) -i "$(ASSET_OBJ_DIR)/$<" -o "$(ASSET_NYA_DIR)/$@"

$(ASSET_NYA_DIR)/$(MODELS_NYA):$(MODELS_OBJ_P)
	$(info converting $< into $@)
	$(MODEL_CONVERTER) -i "$<" -o "$@"



