DEFINES+=PROJECT_CONF_H=\"project-conf.h\"

CONTIKI_PROJECT = zigphy-tx zigphy-rx

all: $(CONTIKI_PROJECT)

CONTIKI = ../..
CONTIKI_WITH_RIME = 0
include $(CONTIKI)/Makefile.include
