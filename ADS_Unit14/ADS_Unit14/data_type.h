#if !defined DATA_TYPE
#define DATA_TYPE


enum content_type {ct_number, ct_add, ct_sub, ct_div, ct_mul, ct_lpar, ct_rpar};
struct data_type {
	content_type content;
	int number;
};

// Returns if a given char could be converted into the specific data_type.
// Also returns the data_type via reference.
bool convert(char c, data_type& data);
#endif