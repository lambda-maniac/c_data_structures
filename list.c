#pragma once

#include "integer.h"

#define OK   0
#define FAIL 1

struct __List
{
    u0** data;

    u16 length;
    u16 capacity;
};

typedef struct __List List;

u8 List_init   (List* self);
u8 List_dispose(List* self);

u8 List_realloc(List* self, u16 new_capacity);

u8 List_insert(List* self, u16 at, u0 * element);
u8 List_remove(List* self, u16 at, u0** element);

u8 List_set(List* self, u16 at, u0 * element);
u8 List_get(List* self, u16 at, u0** element);

u8 List_init(List* self)
{
    self->data     = NULL;
    self->length   = NULL;
    self->capacity = NULL;

    if (List_realloc(self, 2) == FAIL)
        return FAIL;

    return OK;
}

u8 List_dispose(List* self)
{
    free(self->data);
    return OK;
}

u8 List_realloc(List* self, u16 new_capacity)
{
    self->data = realloc( self->data, new_capacity * sizeof (u0*) );

    if (self->data == NULL)
        return FAIL;

    self->capacity = new_capacity;

    return OK;
}

u8 List_insert(List* self, u16 at, u0* element)
{
    if (self->length < at)
        return FAIL;

    if (self->length >= self->capacity)
        if (List_realloc(self, self->capacity * 1.5) == FAIL)
            return FAIL;

    // Not out of bounds, we have capacity.
    //               ~~~~~~~~~~~v
    for (u16 index = self->length; index > at; --index)
        self->data[index] = self->data[index - 1];

    self->data[at] = element;

    ++(self->length);

    return OK;
}

u8 List_remove(List* self, u16 at, u0** element)
{
    if ( self->length <= 0 
    ||   self->length <= at )
        return FAIL;

    u0* value = self->data[at];

    for (u16 index = at; index < self->length - 1; ++index)
        self->data[index] = self->data[index + 1];

    --(self->length);

    if (element != NULL)
        *element = value;

    return OK;
}

u8 List_get(List* self, u16 at, u0** element)
{
    if (at >= self->length)
        return FAIL;

    *element = self->data[at];

    return OK;
}

u8 List_set(List* self, u16 at, u0* element)
{
    if (at >= self->length)
        return FAIL;

    self->data[at] = element;

    return OK;
}
