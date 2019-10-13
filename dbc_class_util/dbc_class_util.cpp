#include <iostream>
#include <stdio.h>

struct dbc_header
{
	uint32_t magic;
	uint32_t record_count;
	uint32_t field_count;
	uint32_t record_size;
	uint32_t string_block_size;
};

//template<typename record_type>
//struct dbc_file
//{
//	dbc_header header;
//	record_type records[header.record_count];
//	char string_block[header.string_block_size];
//};

struct gt_chance_to_melee_crit_dbc
{
	float_t data;
};

int main()
{
	FILE* file;
	errno_t err = fopen_s(&file, "gtChanceToMeleeCrit.dbc", "r");
	if (!err && file != NULL)
	{
		dbc_header header;
		fread(&header, sizeof(dbc_header), 1, file);

		for (int i = 1; i <= header.record_count; i++)
		{
			gt_chance_to_melee_crit_dbc record;
			fread(&record, sizeof(record), 1, file);
			std::cout << i << " - " << record.data << "\n";
		}
		std::cout << std::endl;
	}
}
