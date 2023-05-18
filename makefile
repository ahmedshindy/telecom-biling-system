CC := gcc 
CC_FLAGS:= -g 

run:Telecom_biling_system.elf
	@./Telecom_biling_system.elf

Telecom_biling_system.elf:main.o  telecom_biling_system.o
	$(CC) $(CC_FLAGS) $^ -o $@


main.o:main.c
	$(CC) $(CC_FLAGS) -c $<

telecom_biling_system.o:telecom_biling_system.c
	$(CC) $(CC_FLAGS) -c $<

clean:
	rm *.o *.elf