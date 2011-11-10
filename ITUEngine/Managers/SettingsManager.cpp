#include <iostream>
#include <string>
#include <vector>

#include <Managers/SettingsManager.hpp>
#include <ThirdParty/pugixml/pugixml.hpp>
#include <Utils/StringUtils.hpp>
#include <Assertion.hpp>

// General Functions
void SettingsManager::StartUp()
{
	// Loads the various values from the XML-file.
	pugi::xml_parse_result result = doc.load_file("Settings.xml");

	std::string errormessage = "Error during parsing of XML file: " + std::string(result.description());
	ASSERT_MSG(-1, errormessage.c_str());

	std::cout << "Result of import of \"Settings.xml\": " << result.description() << std::endl;

	// Left-over test-lines - also shows usage:
	/*
	std::cout << "Win!: " << this->GetOption("video/resolution/width");
	std::cout << " (video/resolution/width)" << std::endl;
	this->SetOption("video/resolution/width", "500");
	std::cout << "Win!: " << this->GetOption("video/resolution/width");
	std::cout << " (video/resolution/width)" << std::endl;
	*/
}

void SettingsManager::ShutDown() 
{
	this->SaveXML();
	// ...along with some other stuff that should probably happen.
}

void SettingsManager::SaveXML()
{
	// Writes the current settings to the XML-file.
	// In the end, this is probably the only thing ShutDown() should so.
}

// Functions for Setting Option-values.
void SettingsManager::SetOption(std::string identifier, std::string value)
{
	std::string result, errormessage;
	bool writeResult;
	identifier = "settings/" + identifier;

	// Returns the value of a given option, and "null" if not found.
	// Tokenizes the XML-tree, and scans until only the last token is left.
	std::vector<std::string> tokens = StringUtils::tokenize(identifier, "/");

	auto length = tokens.size();
	auto node = doc.root();
	auto it = tokens.begin();

	for (unsigned int i = 0; i < length - 1; i++)
	{
		node = node.child((*it).c_str());
		it++;
	}

	std::string name = (*it);

	// Check if the identifier is to an attribute or a node
	tokens = StringUtils::tokenize(name, ".");

	errormessage = "Tokenization of '" + name + "' resulted in a zero-element array. Oops?";
	ASSERT_MSG((tokens.size() > 0), errormessage.c_str());

	// Checks for valid identifier (can't have dual attribute signs (.))
	errormessage = "The identifier '" + identifier + "' is malformed.";
	ASSERT_MSG((tokens.size() == 1 || tokens.size() == 2), errormessage.c_str());

	// Checks for valid value (that the identifier actually has a value in the XML file)
	// The actual errormessage is used within the if-statements below
	errormessage = "The identifier '" + identifier + "' doesn't exist in the settings file.";
	
	// There was no attribute
	if (tokens.size() == 1)
	{
		result = node.child_value(name.c_str());
		ASSERT_MSG((result != ""), errormessage.c_str());
		writeResult = node.child(name.c_str()).set_value(value.c_str());
	}
	// There was an attribute
	else
	{
		result = node.child(tokens[0].c_str()).attribute(tokens[1].c_str()).value();
		ASSERT_MSG((result != ""), errormessage.c_str());
		writeResult = node.child(tokens[0].c_str()).attribute(tokens[1].c_str()).set_value(value.c_str());
	}

	// Returns an error if the set_value()-failed
	errormessage = "The identifier '" + identifier + "' couldn't be written to the settings tree.";
	ASSERT_MSG((writeResult == 0), errormessage.c_str());
}

void SettingsManager::SetOptionToDefault(std::string identifier)
{
	this->SetOption(identifier, this->GetOption(identifier + ".default"));
}

void SettingsManager::SetAllOptionsToDefaults()
{
	// Resets all the variables to their defaults, if available.
}

// Functions for Getting Option-values.
std::string SettingsManager::GetOption(std::string identifier)
{
	std::string result, errormessage;

	identifier = "settings/" + identifier;

	// Returns the value of a given option, and "null" if not found.
	// Tokenizes the XML-tree, and scans until only the last token is left.
	std::vector<std::string> tokens = StringUtils::tokenize(identifier, "/");

	auto length = tokens.size();
	auto node = doc.root();
	auto it = tokens.begin();

	for (unsigned int i = 0; i < length - 1; i++)
	{
		node = node.child((*it).c_str());
		it++;
	}
	
	std::string name = (*it);

	// Check if the identifier is to an attribute or a node
	tokens = StringUtils::tokenize(name, ".");

	errormessage = "Tokenization of '" + name + "' resulted in a zero-element array. Oops?";
	ASSERT_MSG((tokens.size() > 0), errormessage.c_str());

	// Checks for valid identifier (can't have dual attribute signs (.))
	errormessage = "The identifier '" + identifier + "' is malformed.";
	ASSERT_MSG((tokens.size() == 1 || tokens.size() == 2), errormessage.c_str());

	// There was no attribute
	if (tokens.size() == 1)
	{
		result = node.child_value(name.c_str());
	}
	// There was an attribute
	else
	{
		result = node.child(tokens[0].c_str()).attribute(tokens[1].c_str()).value();
	}

	// Checks for valid value (that the identifier actually has a value in the XML file)
	errormessage = "The identifier '" + identifier + "' doesn't exist in the settings file.";
	ASSERT_MSG((result != ""), errormessage.c_str());
	
	return result;
}

std::string SettingsManager::GetOptionDefault(std::string identifier)
{
	return this->GetOption(identifier + ".default");
}