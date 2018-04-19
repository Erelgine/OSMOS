ENTRY(_start)										/* We specify the main point of the executable ELF binary */

SECTIONS
{
	.boot :											/* The section for the multiboot specification */
	{
		*(.multiboot)								/* We tell that the linker MUST put the multiboot specification into the top of the binary */
	}

	.text :											/* The section for the code part of the binary */
	{
		*(.text)									/* We indicate that the code is before data such as strings */
		*(.bss)										/* We put the data after the code */
	}	
}