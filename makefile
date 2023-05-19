CC := gcc 
CC_FLAGS:= -g 


Telecom_biling_system.elf:main.o  telecom_biling_system.o
	$(CC) $(CC_FLAGS) $^ -o $@

run:Telecom_biling_system.elf
	@./Telecom_biling_system.elf

main.o:main.c
	$(CC) $(CC_FLAGS) -c $<

telecom_biling_system.o:telecom_biling_system.c
	$(CC) $(CC_FLAGS) -c $<

clean:
	rm *.o *.elf