#include <iostream>
#include <vector>
#include <queue>
#include <set>
#include <functional>
#include <string>
#include <algorithm>

using namespace std;

typedef std::pair<char, std::vector<int> > CharCoder;



class FrequencyPairNode 
{
public:
	int leftIndex;
	int rightIndex;
	int index;
	char symbol;
	int frequence;
	std::vector<CharCoder> result;
	std::vector<FrequencyPairNode> frequency_symbol_list;

	FrequencyPairNode(char symbol, int frequence, int index): symbol(symbol), frequence(frequence), leftIndex(-1), rightIndex(-1), index(index) {}

	void print() 
	{
		std::cout << "Symbol: " << symbol << ", frequences: " << frequence << std::endl;
	}

	bool is_leaf() 
	{
		return leftIndex < 0 && rightIndex < 0;
	}
};

std::vector<CharCoder> resultFrequency;
std::vector<FrequencyPairNode> frequency_symbol_list;
std::vector<int> bites;

int decode_char(char c)
{
	int value = int(c);
	if (value < 0) 
	{
		value += 256;
	}
	return value;
}

void fill_values(FrequencyPairNode& current) 
{
	if(current.is_leaf()) 
	{
		bool is_empty = false;
		if (bites.empty()) 
		{
			bites.push_back(0);
			is_empty = true;
		}
		
		CharCoder current_code = std::make_pair(current.symbol, std::vector<int>(bites));
		resultFrequency.push_back(current_code);
		if (is_empty) 
		{
			is_empty = false;
			bites.pop_back();
		}
		return;
	}

	// go left child
	bites.push_back(0);
	FrequencyPairNode leftNode = frequency_symbol_list[current.leftIndex];

	fill_values(leftNode);
	bites.pop_back();
	// go right child
	bites.push_back(1);
	FrequencyPairNode rightNode = frequency_symbol_list[current.rightIndex];
	fill_values(rightNode);
	bites.pop_back();
}

struct Vertex 
{
	int left_index;
	int right_index;
	char position;
	int frequency;
};

FrequencyPairNode merge(FrequencyPairNode left, FrequencyPairNode right, int index) 
{
	FrequencyPairNode node(' ', left.frequence + right.frequence, index);
	node.leftIndex = left.index;
	node.rightIndex = right.index;
	return node;
}

class Comparison 
{
public:
	bool operator() (const FrequencyPairNode& left, const FrequencyPairNode& right) const 
	{
		if (left.frequence > right.frequence) 
		{
			return true;
		}
		if (left.frequence < right.frequence) 
		{
			return false;
		}
		return left.symbol < right.symbol;
	}
};

void write_buffer(std::string& buffer, std::vector<int>& bytes) 
{
	int mod = bytes.size() % 8;
	if (mod == 0) 
	{
		mod += 8;
	}
	buffer += char(mod);
	int code = 0;
	for (int i = 0; i < bytes.size(); ++i) 
	{
		code = code * 2 + bytes[i];
		if (i % 8 == 7) 
		{
			buffer += char(code);
			code = 0;
		}
	}

	if (bytes.size() % 8 != 0) 
	{
		buffer += char(code);
	}
}


void compress_string(const std::string& source, std::string& compressed) 
{
	std::vector<int> frequency_list(256, 0); 

	for (size_t index = 0; index < source.length(); ++index) 
	{
		int value = source[index];
		if (value < 0) 
		{
			value += 256;
		}
		frequency_list[value]++;
	}
	frequency_symbol_list.clear();
	int size = 0;
	for (size_t index = 0; index < 256; ++index) 
	{
		if (frequency_list[index] > 0) 
		{
			frequency_symbol_list.push_back(FrequencyPairNode(index, frequency_list[index], size));
			size++;
		}
	}
	typedef std::priority_queue<FrequencyPairNode, std::vector<FrequencyPairNode>, Comparison> ComparisonPriorityQueue;
	ComparisonPriorityQueue frequency_queue(Comparison(), frequency_symbol_list);

	FrequencyPairNode pairf = frequency_queue.top();
	
	while (frequency_queue.size() >= 2) 
	{
		FrequencyPairNode first = frequency_queue.top();
		frequency_queue.pop();
		FrequencyPairNode second = frequency_queue.top();
		frequency_queue.pop();
		FrequencyPairNode merged_node = merge(first, second, size);
		frequency_symbol_list.push_back(merged_node);
		size++;
		frequency_queue.push(merged_node);
	}

	FrequencyPairNode root = frequency_queue.top();

	int index = root.index;
	frequency_queue.pop();
	resultFrequency.clear();

	fill_values(root);
	
	compressed.clear();
	compressed += char(int(resultFrequency.size()));
	for (int i = 0; i < resultFrequency.size(); ++i) 
	{
		int code = 0;
		for (int j = 0; j < resultFrequency[i].second.size(); ++j) 
		{
			code = code * 2 + resultFrequency[i].second[j];
		}
		compressed += resultFrequency[i].first;
		compressed += char(int(resultFrequency[i].second.size()));
		for (int k = 0; k < resultFrequency[i].second.size(); ++k) 
		{
			compressed += char('0' + resultFrequency[i].second[k]);
		}
	}
	
	std::vector<int> coded_symbols;
	for (size_t index = 0; index < source.length(); ++index) 
	{
		for (int j = 0; j < resultFrequency.size(); ++j) 
		{
			if (resultFrequency[j].first == source[index]) 
			{
				for (int k = 0; k < resultFrequency[j].second.size(); ++k) 
				{
					coded_symbols.push_back(resultFrequency[j].second[k]);
				}
			}
		}
	}

	write_buffer(compressed, coded_symbols);
}

void decompress_string(const std::string& compressed, std::string& result) 
{
	int size = decode_char(compressed[0]);
	std::vector<char> symbols;
	std::vector<int> codes;
	std::vector<int> byte_sizes;
	std::vector<std::string> byte_strings(size);
	int current_index = 1;
	for (int i = 0; i < size; ++i) 
	{
		char symbol = compressed[current_index];
		symbols.push_back(compressed[current_index]);
		current_index++;

		int byte_size = compressed[current_index];
		byte_sizes.push_back(compressed[current_index]);
		current_index++;
	
		for (int k = 0; k < byte_size; ++k) 
		{
			byte_strings[i] += compressed[current_index];
			current_index++;
		}
	}
	

	int mod = compressed[current_index];
	current_index++;

	std::vector<int> bytes;
	for (int index = current_index; index < compressed.length(); ++index) 
	{
		int symbol = decode_char(compressed[index]);
		int byte_index = 8;
		if (index + 1 == compressed.length()) 
		{
			byte_index = mod;
		}
		for (int j = byte_index - 1; j >= 0; --j) 
		{
			int byte = (symbol & (1 << j)) >> j;
			bytes.push_back(byte);
		}
	}
	
	result.clear();
	std::string current_string = "";
	for (int i = 0; i < bytes.size(); ++i) 
	{
		current_string += char(bytes[i] + '0');
		int found_index = -1;
		for (int j = 0; j < byte_strings.size(); ++j) 
		{
			if (current_string == byte_strings[j]) 
			{
				found_index = j;
				current_string = "";
			}	
		}
		if (found_index >= 0) 
		{
			result += symbols[found_index];
		}
	}
}