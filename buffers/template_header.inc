#define __DECLARE_BUFFER_INTERFACE(DATATYPE, NAME)	     \
typedef struct				     \
{				     \
  DATATYPE **reserve;			     \
  unsigned int max;			     \
  unsigned int allocated;			     \
  unsigned int free;			     \
} NAME ## _buffers_t;			     \
				     \
typedef DATATYPE * NAME ## _field_t;		     \
				     \
extern  NAME ## _buffers_t g_ ## NAME ## _buffers;	     \
				     \
void allocate_ ## NAME ## _buffer();		     \
void free_unused_ ## NAME ## _buffers();		     \
				     \
NAME ## _field_t get_ ## NAME ## _field();		     \
NAME ## _field_t get_ ## NAME ## _field_annotated(char const *note); \
void return_ ## NAME ## _field(NAME ## _field_t *field);	     \
void initialize_ ## NAME ## _buffers(unsigned int max);	     \
void finalize_ ## NAME ## _buffers();
