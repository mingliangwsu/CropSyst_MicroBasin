#include <corn/bnfparse.h>
#include <corn/vv_entry.h>
//______________________________________________________________________________
class BNF_token
:public CORN_association
,public CORN_string
{
//	 CORN_string token;
public:
	inline BNF_token(const CORN_string &token_str)
	:CORN_association()
//	,token(token_str)
	,CORN_string(token_str)
	{}
   
   inline virtual const char    *key_string (std::string &buffer)          const   //180820
      { buffer.assign(*this); return buffer; }
/*180820       
	virtual CORN_string &get_key(CORN_string &key) const
	{ key.assign(*this/*token*/); return key; };
*/   
};
//______________________________________________________________________________
class BNF_token_tree
: public BNF_token
, public CORN_association_list  // tokens_this_level
{
public:
//	BNF_token_tree(CORN_string &raw_expression,CORN_string &i_token);

	BNF_token_tree(CORN_string &raw_expression,CORN_string &i_token,char terminator = 0);
//	:CORN_association_list() //tokens_this_level()
//	,BNF_token(i_token)
//	{};

	// This constructor is used when we split tokens into terms and factors
	inline BNF_token_tree()
	:CORN_association_list() //tokens_this_level()
	,BNF_token("")
	{};

	void pop_token(CORN_string &expression,CORN_string token);
};
//______________________________________________________________________________
BNF_expression::BNF_expression
(BNF_parser				 &i_parent_parser
,BNF_token_tree &tokenized_expression)
{
	while (tokenized_expression.count())
	{
		BNF_token_tree term_tokens;

		// build a list of tokens composing terms and make a list of them
		BNF_token *token = (BNF_token *)tokenized_expression.pop_at_head();
		while (token && (token->CORN_string::compare("|")))
		{
			term_tokens.CORN_association_list::append(token);
			token = (BNF_token *)tokenized_expression.pop_at_head();
		};

		BNF_term *new_term = new BNF_term(i_parent_parser,term_tokens);
		terms.append(new_term);
	};
};
//______________________________________________________________________________
BNF_term::BNF_term
(BNF_parser				 &i_parent_parser
,BNF_token_tree &tokenized_term)
:CORN_list_item()
//,parent_parser(i_parent_parser)
{
	while (tokenized_term.count())
	{

//		BNF_token_tree factor_tokens;

		// build a list of tokens composing terms and make a list of them
		BNF_token_tree *token_tree = (BNF_token_tree *)tokenized_term.pop_at_head();

		if (token_tree)
		{  BNF_factor *factor = 0;
			if (token_tree->CORN_string::compare("\""))
				factor = new BNF_literal_terminal(*token_tree);
			if (token_tree->CORN_string::compare("("))
			  factor = new BNF_precedence(i_parent_parser,*token_tree);
			if (token_tree->CORN_string::compare("{"))
				factor = new BNF_repetition(i_parent_parser,*token_tree);
			if (token_tree->CORN_string::compare("["))
				factor = new  BNF_optional(i_parent_parser,*token_tree);

			if (token_tree->CORN_string::c_str()[0] == '<')
			{
				CORN_string data_type_label(token_tree->c_str());
				data_type_label.strip(string::Leading,'<');
				data_type_label.strip(string::Trailing,'>');
				factor = i_parent_parser.identify_data_type_factor(token_tree->c_str());
			};

			BNF_rule *rule = i_parent_parser.get_rule_identifier(*token_tree);
			if (rule)
				factor = new BNF_rule_identifier(rule);
			if (!factor)
			{
				//if we still don't have a factor, it must be a terminal
				factor = new BNF_terminal(*token_tree);
			};
			factors.append(factor);
			delete token_tree;
		};
	};
};

/*
syntax     ::=  { rule }
rule       ::=  identifier  "::="  expression
expression ::=  term { "|" term }
term       ::=  factor { factor }
factor     ::=  identifier |
					 quoted_symbol |
					 "("  expression  ")" |
					 "["  expression  "]" |
					 "{"  expression  "}"
identifier ::=  letter { letter | digit }
quoted_symbol ::= """ { any_character } """
*/
//______________________________________________________________________________
BNF_parser::BNF_parser(CORN_association_list &raw_rules)
: rules()
{
	add_rules(raw_rules);
};
//______________________________________________________________________________
void BNF_parser::add_rules(CORN_association_list &raw_rules)
{
	for (VV_unexpected_entry *raw_rule = (VV_unexpected_entry *)raw_rules.move_to_head()
		 ;raw_rule
		 ;raw_rule = (VV_unexpected_entry *)raw_rules.move_to_next())
	{
		std::string identifier; //180820 
      key_string(identifier); //180820
		//180820 raw_rule->get_key(identifier);
		CORN_string raw_expression(raw_rule->get());
		BNF_token_tree token_tree(raw_expression,"");
		BNF_rule *rule = new BNF_rule(identifier,*this,token_tree);
		rules.append(rule);
	};
};

BNF_rule::BNF_rule
(const CORN_string &i_identifier
,BNF_parser				 &i_parent_parser
,BNF_token_tree &i_tokenized_expression)
:identifier(i_identifier)
,expression(i_parent_parser,i_tokenized_expression)
{
};
//______________________________________________________________________________


BNF_token_tree::BNF_token_tree
(CORN_string &raw_expression
,CORN_string &i_token
,char terminator )
:CORN_association_list() //tokens_this_level()
,BNF_token(i_token)
{
	bool end_sub_expr = false;
	do
	{
		CORN_string token;
		pop_token(raw_expression,token);
		if (token[0] == terminator)
			end_sub_expr = true;
		else
		{
			char matching_char = 0;
			if (token == "(")   matching_char = ')';
			if (token == "\"")  matching_char = '\"';
			if (token == "{")   matching_char = '}';
			if (token == "[")   matching_char = ']';
			if (matching_char)
			{
				BNF_token_tree *sub_tree = new BNF_token_tree(raw_expression,token,matching_char);
				CORN_association_list::append(sub_tree);
			}
			else
			{
				BNF_token *leaf = new BNF_token(token);
				CORN_association_list::append(leaf);
			};
		};
	} while (raw_expression.length() && !end_sub_expr);
};


bool BNF_parser::parse_file(const char *name_of_file_to_parse)
{
	ifstream file_to_parse(name_of_file_to_parse);
	BNF_rule *syntax_rule = (BNF_rule *)rules.find("syntax");

	if (!syntax_rule)
	  syntax_rule = (BNF_rule *)rules.move_to_head();

	return syntax_rule->parse_stream(file_to_parse);
};
//______________________________________________________________________________
bool BNF_rule::parse_stream(istream &strm_to_parse)
{
	return expression.parse_stream(strm_to_parse);
};
//______________________________________________________________________________
bool BNF_expression::parse_stream(istream &strm_to_parse)
{
	bool parsed = false;
	uint32 current_position = strm_to_parse.tellg();
	for
	(BNF_term *term = (BNF_term *)terms.move_to_head()
	;term && !parsed
	;term = (BNF_term *)terms.move_to_next())
	{
		parsed = term->parse_stream(strm_to_parse);
		if (!parsed)
			strm_to_parse.seekg(current_position);
		else
			current_position = strm_to_parse.tellg();
	};
	return parsed;
};
//______________________________________________________________________________
bool BNF_term::parse_stream(istream &strm_to_parse)
{
	for (BNF_factor *factor= (BNF_factor *)factors.move_to_head()
		 ;factor
		 ;factor = (BNF_factor *)factors.move_to_next())
	{  // If any of the factors can not be parses
		// this cannot be the term we are searching for.
		if (!factor->parse_stream(strm_to_parse))
		  return false;
	};
	return true;
};
//______________________________________________________________________________
BNF_data_factor *BNF_parser::identify_data_type_factor(const CORN_string data_type_label)
{
	if (data_type_label == "char") 	return new BNF_char_data_factor();
/*NYI
	if (data_type_label == "int8") 	return new BNF_int8_data_factor(true);
	if (data_type_label == "int16") 	return new BNF_int16_data_factor(true);
	if (data_type_label == "int32") 	return new BNF_int32_data_factor(true);
	if (data_type_label == "uint8") 	return new BNF_int8_data_factor(false);
	if (data_type_label == "uint16") return new BNF_int16_data_factor(false);
	if (data_type_label == "uint32") return new BNF_int32_data_factor(false);
	if (data_type_label == "float32")return new BNF_float32_data_factor();
	if (data_type_label == "float32")return new BNF_float32_data_factor();
*/
	if (data_type_label == "integer")return new BNF_integer_data_factor();
	if (data_type_label == "number") return new BNF_number_data_factor();
	if (data_type_label == "string") return new BNF_string_data_factor();

	int count_pos = data_type_label.find("@");
	if (count_pos != NPOS)
	{
		CORN_string data_type(data_type_label,0,count_pos);
		count_pos++;
		CORN_string count_str(data_type_label,count_pos);
		int count = atoi(count_str.c_str());
		if (data_type == "integer")return new BNF_integer_data_factor(count);
		if (data_type == "number") return new BNF_number_data_factor(count);
		if (data_type == "string") return new BNF_string_data_factor(count);
	};
	// Default to a string factor.
	BNF_string_data_factor(0);
};
//______________________________________________________________________________






