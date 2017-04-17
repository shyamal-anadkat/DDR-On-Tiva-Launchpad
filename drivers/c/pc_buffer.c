// Copyright (c) 2015, Joe Krachey
// All rights reserved.
//
// Redistribution and use in source or binary form, with or without modification, 
// are permitted provided that the following conditions are met:
//
// 1. Redistributions in source form must reproduce the above copyright 
//    notice, this list of conditions and the following disclaimer in 
//    the documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
// THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
// PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR 
// CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
// EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
// PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
// OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
// WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING 
// NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, 
// EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#include "pc_buffer.h"

//*****************************************************************************
// Initializes a Producer-Consumer circular buffer.  Be sure to allocate 
// memory using malloc for the array field.
// 
// Parameters
//    buffer  :   The address of the circular buffer.
//    size:       Number of entries in the circular buffer.
//*****************************************************************************
void pc_buffer_init(PC_Buffer *buffer, uint16_t buffer_size){
		buffer->array = (char *)malloc(buffer_size* sizeof(char));
	  buffer->BUFFER_SIZE = buffer_size;
	  buffer->consume_count = 0; 
	  buffer->produce_count = 0;
}

//*****************************************************************************
// Adds a character to the circular buffer.
// 
// Parameters
//    buffer  :   The address of the circular buffer.
//    data    :   Character to add.
//*****************************************************************************
void pc_buffer_add(PC_Buffer *buffer, char data)
{
	buffer->array[buffer->produce_count%buffer->BUFFER_SIZE] = data;
	buffer->produce_count ++;
}

//*****************************************************************************
// Removes the oldest character from the circular buffer.
// 
// Parameters
//    buffer  :   The address of the circular buffer.
//    data    :   Address to place the oldest character.
//*****************************************************************************
void pc_buffer_remove(PC_Buffer *buffer, char *data)
{
	*data = buffer->array[buffer->consume_count%buffer->BUFFER_SIZE];
	 buffer->consume_count ++;
}

//*****************************************************************************
// Returns true if the circular buffer is empty.  Returns false if it is not.
// 
// Parameters
//    buffer  :   The address of the circular buffer.
//*****************************************************************************
bool pc_buffer_empty(PC_Buffer *buffer){

	return(buffer->consume_count == buffer->produce_count);
}

//*****************************************************************************
// Returns true if the circular buffer is full.  Returns false if it is not.
// 
// Parameters
//    buffer  :   The address of the circular buffer.
//*****************************************************************************
bool pc_buffer_full(PC_Buffer *buffer)
{
	return (buffer->produce_count - buffer->consume_count == buffer->BUFFER_SIZE);
}
