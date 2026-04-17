#include <iostream>
#include <string>

#include "includes.hpp"
#include <string_view>
#include "func_transformer.h"

static auto build_function(
	const std::string_view input_file, 
	const std::string_view output_file, 
	const std::string_view start_rva, 
	const std::string_view end_rva)
{
	func_trans transformer;
	
	if (!transformer.ImportFile(input_file))
		return false;

	if (!transformer.Build(std::stoi(start_rva.data()), std::stoi(end_rva.data())))
		return false;

	if (!transformer.ExportFile(output_file))
		return false;

	return true;
}


auto main(i32 argc, i8* argv[]) -> i32
{
	return (build_function(
		argv[1], //input file
		argv[2], //output file
		argv[3], //start rva
		argv[4])); //end rva
}