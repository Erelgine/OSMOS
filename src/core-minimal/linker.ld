/* We specify the main point of the executable ELF binary */
ENTRY(_start)

SECTIONS
{
	/* The code is loaded on address 0x00100000 */
	. = 0x00100000;

	/* The section for the multiboot specification */
	.boot :
	{
		/* We tell that the linker MUST put the multiboot specification into the top of the binary */
		*(.multiboot)
	}

	/* The section for the code part of the binary */
	.text ALIGN(0x1000) :
	{
		*(.text)
	}

	.rodata ALIGN(0x1000) :
	{
		/* The following is for global constructors support in C++ */
		start_ctors = .;
        *(SORT(.ctors*))
        end_ctors = .;

        /* The following is for global destructors support in C++ */
        start_dtors = .;
        *(SORT(.dtors*))
        end_dtors = .;

        /* The .rodata comes just after the ctors/dtors */
        *(.rodata*)

        /* Dedicaced GCC vague linkage section for .rodata */
        *(.gnu.linkonce.r*)
	}

	/* The data (such as strings/variables) for the binary */
	.data ALIGN(0x1000) :
	{
		/* The data is in it's proper part */
		*(.data)
		/* Dedicaced GCC vague linkage section for .data */
        *(.gnu.linkonce.d*)
	}

	/* The Block Started by Symbol part of the binary */
	.bss :
	{
		/* Marking the beggining of .bss */
		sbss = .;

		/* .bss comes here */
		*(.bss)

		/* Dedicaced GCC vague linkage section for .bss */
        *(.gnu.linkonce.b*)

        /* Marking the end of .bss */
		ebss = .;
	}

	/* We tell to the linker that we discard .comment sections */
	/DISCARD/ :
	{
		*(.comment)
	}
}