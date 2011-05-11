.PHONY: clean All

All:
	@echo ----------Building project:[ DrawGin - Debug ]----------
	@cd "DrawGin" && "$(MAKE)" -f "DrawGin.mk"
clean:
	@echo ----------Cleaning project:[ DrawGin - Debug ]----------
	@cd "DrawGin" && "$(MAKE)" -f "DrawGin.mk" clean
