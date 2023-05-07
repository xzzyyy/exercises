#include <string_view>
#include <vector>
#include <deque>
#include <map>
#include <iostream>
#include <sstream>
using namespace std;


//#define DEBUG
#ifdef DEBUG
#define DEBUG_MSG(str) do { cout << str << endl; } while(false)
#else
#define DEBUG_MSG(str) do {  } while (false)
#endif


constexpr int QUERY_SZ = -1;
constexpr string_view STR_NOT_FOUND = "Not Found!";


vector<int> read_nums(int sz) {
    if (sz == QUERY_SZ)
        cin >> sz;

    vector<int> nums;
    for (int i = 0; i < sz; ++i) {
        int n;
        cin >> n;
        nums.push_back(n);
    }
    return nums;
}


struct Tag {
    Tag(int lvl, deque<string>& lines);
    virtual ~Tag();

    string get_tag_id() const;
    static string get_token(istringstream& iss);
    string query(istringstream& q_iss) const;

private:
    string tag_id;
    int lvl;
    map<string, string> attrs;
    map<string, Tag*> child_tags;

    void parse_tag(deque<string>& lines);
    void parse_attrs(istringstream& ss);
    string str_attrs() const;
    string str_child_tags() const;
};

Tag::Tag(int lvl, deque<string>& lines)
        : lvl(lvl) {
    DEBUG_MSG(string(4 * lvl + 1, '.'));
    parse_tag(lines);
}

Tag::~Tag() {
    DEBUG_MSG(string(lvl * 4, ' ') << "Tag::~Tag");
    for (auto id_tag : child_tags)
        delete id_tag.second;
}

string Tag::get_tag_id() const {
    return tag_id;
}

string Tag::get_token(istringstream& iss) {
    string token;
    char c;

    do {
        iss >> c;
        if (!iss)
            break;
        token += c;
    } while (c != '.' && c != '~');

    if (iss) {
        iss.unget();
        token.pop_back();
    }
    //DEBUG_MSG("Tag::get_token | token: [" << token << "]");
    return token;
}

string Tag::query(istringstream& q_iss) const {
    char delim;
    q_iss >> delim;

    string token = get_token(q_iss);
    DEBUG_MSG(string(lvl * 4, ' ') << "Tag::query | get_tag_id: [" << get_tag_id()
              << "]; delim: [" << delim << "]; token: [" << token << "]");

    if (delim == '.')
        return child_tags.count(token) ? child_tags.at(token)->query(q_iss) : string(STR_NOT_FOUND);
    else if (delim == '~')
        return attrs.count(token) ? attrs.at(token) : string(STR_NOT_FOUND);

    throw;
}

void Tag::parse_tag(deque<string>& line_deq) {
    string line = line_deq.front();
    istringstream iss(line);
    DEBUG_MSG(string(lvl * 4, ' ') << __func__ << " | line: [" << line << "]");

    char dum_c;
    iss >> dum_c;
    iss >> tag_id;

    if (tag_id.back() == '>')
        tag_id.pop_back();
    else
        parse_attrs(iss);

    line_deq.pop_front();

    while ((line = line_deq.front()).substr(0, 2) != "</") {
        Tag* t = new Tag(lvl + 1, line_deq);
        child_tags[t->get_tag_id()] = t;
    }

    DEBUG_MSG(string(lvl * 4, ' ') << __func__ << " | line: [" << line << "]");
    line_deq.pop_front();       // skipping closing tag

    DEBUG_MSG(string(lvl * 4, ' ') << __func__
              << " | get_tag_id: [" << get_tag_id()
              << "]; str_attrs: [" << str_attrs()
              << "]; str_child_tags: [" << str_child_tags() << "]");
}

void Tag::parse_attrs(istringstream& iss) {
    string word, key, val, dum_s;
    char dum_c;

    bool last = false;
    while(!last) {
        iss >> key >> dum_s >> dum_c >> val;
        DEBUG_MSG(string(lvl * 4, ' ') << "Tag::parse_attrs | key: [" << key <<
                  "], dum_s: [" << dum_s << "], dum_c: [" << dum_c << "], val: [" << val << "]");

        if (val.back() == '>')
        {
            last = true;
            val.pop_back();
        }
        val.pop_back();

        attrs[key] = val;
    }
}

string Tag::str_attrs() const {
    string res;
    int i = 0;
    for (const auto& att_kv : attrs)
        res += (i++ ? "; " : "") + att_kv.first + ": " + att_kv.second;
    return res;
}

string Tag::str_child_tags() const {
    string res;
    int i = 0;
    for (const auto& id_tag : child_tags)
        res += (i++ ? ", " : "") + id_tag.first;
    return res;
}


int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    vector<int> nums_str = read_nums(2);
    int line_cnt = nums_str[0];
    int q_cnt = nums_str[1];
    //DEBUG_MSG("[" << line_cnt << " " << q_cnt << "]");

    deque<string> tag_strs;
    string line;
    getline(cin, line);     // skipping leftover "\n" line
    for (int i = 0; i < line_cnt; ++i) {
        getline(cin, line);
        //DEBUG_MSG("[" << line << "]");
        tag_strs.push_back(line);
    }

    map<string, Tag*> lvl1_tags;
    while (tag_strs.size() != 0) {
        Tag* t = new Tag(0, tag_strs);
        lvl1_tags[t->get_tag_id()] = t;
    }

    for (int i = 0; i < q_cnt; ++i) {
        DEBUG_MSG(".");
        getline(cin, line);
        DEBUG_MSG("main, query | line: [" << line << "]");
        istringstream iss(line);

        string tag = Tag::get_token(iss);
        if (lvl1_tags.count(tag) == 0)
            cout << STR_NOT_FOUND << endl;
        else
            cout << lvl1_tags.at(tag)->query(iss) << endl;
    }

    return 0;
}
