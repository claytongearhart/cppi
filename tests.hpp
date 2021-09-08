// A list of functions made for testing, do not delete as may submit in
// final assmem

template <typename C>
void split(std::string const &s, char const *d, C &ret)
{
  C output;

  std::bitset<255> delims;
  while (*d)
  {
    unsigned char code = *d++;
    delims[code] = true;
  }
  typedef std::string::const_iterator iter;
  iter beg;
  bool in_token = false;
  for (std::string::const_iterator it = s.begin(), end = s.end();
       it != end; ++it)
  {
    if (delims[*it])
    {
      if (in_token)
      {
        output.push_back(typename C::value_type(beg, it));
        in_token = false;
      }
    }
    else if (!in_token)
    {
      beg = it;
      in_token = true;
    }
  }
  if (in_token)
    output.push_back(typename C::value_type(beg, s.end()));
  output.swap(ret);
}