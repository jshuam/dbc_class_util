#include <iostream>
#include <memory>
#include <stdio.h>
#include <vector>

struct dbc_header
{
	uint32_t magic;
	uint32_t record_count;
	uint32_t field_count;
	uint32_t record_size;
	uint32_t string_block_size;

	void to_string()
	{
		std::cout << "\nDBC Header Info:\n";
		std::cout << "Magic Number: " << magic << "\n";
		std::cout << "Record Count: " << record_count << "\n";
		std::cout << "Field Count: " << field_count << "\n";
		std::cout << "Record Size: " << record_size << "\n";
		std::cout << "String Block Size: " << string_block_size << "\n";
	}
};

template<typename record_type>
struct dbc_file
{
	dbc_header header;
	std::vector<record_type> records;
	std::vector<char> string_block;

	dbc_file(dbc_header header)
		:
		header(header),
		records(header.record_count),
		string_block(header.string_block_size)
	{}
};

struct gt_chance_to_melee_crit_dbc
{
	float_t data;
};

struct chr_classes_dbc
{
	uint32_t class_id;
	uint32_t field_01;
	uint32_t display_power;
	uint32_t pet_name_token;
	std::string name;
	std::string name_mask;
	std::string name_female_mask;
	std::string name_male_mask;
	std::string filename;
	uint32_t spell_class_set;
	uint32_t flags;
	uint32_t cinematic_seq_id;
	uint32_t required_expansion;
};

int main()
{
	FILE* file;
	errno_t err = fopen_s(&file, "ChrRaces.dbc", "rb");
	if (!err && file != NULL)
	{
		dbc_header header;
		fread(&header, sizeof(dbc_header), 1, file);
		fseek(file, sizeof(dbc_header) + header.record_count * header.record_size + sizeof(uint32_t), 0);
		std::string test;
		for (int i = 0; i < header.string_block_size; i++)
		{
			char byte;
			fread(&byte, sizeof(char), 1, file);
			test.push_back(byte);
			if (byte == '\0')
				break;
		}
		std::cout << test;

		/*std::vector<char> record(header.record_size);
		fread(&record[0], header.record_size, 1, file);
		for (const char& c : record)
			std::cout << c;*/
		/*dbc_file<gt_chance_to_melee_crit_dbc> dbc(header);
		fread(&dbc.records[0], sizeof(gt_chance_to_melee_crit_dbc), header.record_count, file);
		dbc.records.push_back({ 0.69369f });
		dbc.header.record_count = dbc.records.size();
		fclose(file);

		FILE* output;
		errno_t err = fopen_s(&output, "gtChanceToMeleeCrit.dbc", "wb");
		if (!err && output != NULL)
		{
			fwrite(&dbc.header, sizeof(dbc_header), 1, output);
			fwrite(&dbc.records[0], sizeof(gt_chance_to_melee_crit_dbc), dbc.records.size(), output);
		}*/
	}
}
