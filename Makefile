# Makefile fino: só delega ao CMake. Toda a configuração mora no CMakeLists.txt.
BUILD := build
DEMO  := $(BUILD)/demo
SAIDA := $(BUILD)/saida.txt

.PHONY: all roda verifica limpa

all:
	cmake -S . -B $(BUILD)
	cmake --build $(BUILD)

roda: all
	./$(DEMO)

# O portão: compila (com -Werror, aplicado pelo CMakeLists.txt), roda e exige
# que o programa termine sem erro e que a última linha seja exatamente vivos=0.
verifica: all
	./$(DEMO) > $(SAIDA)
	@cat $(SAIDA)
	@ultima="$$(tail -n 1 $(SAIDA))"; \
	if [ "$$ultima" = "vivos=0" ]; then \
		echo "[verifica] OK: a ultima linha e vivos=0"; \
	else \
		echo "[verifica] FALHOU: a ultima linha e '$$ultima', esperado 'vivos=0'"; \
		exit 1; \
	fi

limpa:
	cmake -E remove_directory $(BUILD)
