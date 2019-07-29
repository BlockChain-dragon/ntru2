RM := rm -rf

TARGET := Uniform-pqNTRUSign-1024

LIBS := -lm -lcrypto

C_SRCS += \
  PQCgenKAT_sign.c \
  ../common/packing.c \
  ../common/param.c \
  ../common/pqNTRUSign.c \
  ../common/rng.c \
  sign.c \
  ../common/crypto_hash_sha512.c \
  ../common/crypto_stream.c \
  ../common/fastrandombytes.c \
  ../common/shred.c \
  ../common/DGS.c \
  ../common/NTT.c \
  ../common/misc.c \
  ../common/poly.c 

OBJS += \
  PQCgenKAT_sign.o \
  ../common/packing.o \
  ../common/param.o \
  ../common/pqNTRUSign.o \
  ../common/rng.o \
  sign.o \
  ../common/crypto_hash_sha512.o \
  ../common/crypto_stream.o \
  ../common/fastrandombytes.o \
  ../common/shred.o \
  ../common/DGS.o \
  ../common/NTT.o \
  ../common/misc.o \
  ../common/poly.o 
  
C_DEPS += \
  PQCgenKAT_sign.d \
  ../common/packing.d \
  ../common/param.d \
  ../common/pqNTRUSign.d \
  ../common/rng.d \
  sign.d \
  ../common/crypto_hash_sha512.d \
  ../common/crypto_stream.d \
  ../common/fastrandombytes.d \
  ../common/shred.d \
  ../common/DSG.d \
  ../common/NTT.d \
  ../common/misc.d \
  ../common/poly.d 

%.o: ../%.c
	@echo 'Building file: $<'
	@echo 'Invoking: Cross GCC Compiler'
	gcc -I/usr/local/include/ -I/usr/include/ -O3 -g3 -Wall -c -fmessage-length=0 -MMD -MP -MF"$(@:%.o=%.d)" -MT"$(@:%.o=%.d)" -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '




# Add inputs and outputs from these tool invocations to the build variables 

# All Target
all: $(TARGET)

# Tool invocations
$(TARGET): $(OBJS) $(USER_OBJS)
	@echo 'Building target: $@'
	@echo 'Invoking: Cross GCC Linker'
	gcc  -o $(TARGET) $(OBJS) $(USER_OBJS) $(LIBS)
	@echo 'Finished building target: $@'
	@echo ' '

# Other Targets
clean:
	-$(RM) $(EXECUTABLES)$(OBJS)$(C_DEPS) $(TARGET)
	-@echo ' '

.PHONY: all clean dependents
.SECONDARY:


