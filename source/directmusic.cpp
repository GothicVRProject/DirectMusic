#include "directmusic.h"

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <filesystem>
#include <cstdio>
#include <string>
#include <stdexcept>
#include <vector>
#include <chrono>
#include <ctime>
#include <algorithm>

#include "logger.h"

using namespace Dx8;

DirectMusic::DirectMusic()
{
}

PatternList DirectMusic::load(const Segment &s)
{
  return PatternList(s, *this);
}

PatternList DirectMusic::load(std::string fsgt)
{
  std::ifstream ifs = implCustomOpen(fsgt);
  // std::ifstream ifs = implCustomOpen(fsgt);

  auto pos = ifs.tellg();
  ifs.seekg(0, std::ios::end);
  auto size = ifs.tellg() - pos;
  ifs.seekg(pos, std::ios::beg);

  std::vector<uint8_t> v(static_cast<size_t>(size));
  if (!ifs.read(reinterpret_cast<char *>(v.data()), v.size()))
  {
    // handle error
  }

  ifs.close();

  try
  {
    auto r = Dx8::Riff(v.data(), v.size());
    auto sgt = Dx8::Segment(r);
    return load(sgt);
  }
  catch (const std::exception &e)
  {
    std::cerr << "Error: " << e.what() << '\n';
    return {};
  }
}

void DirectMusic::addPath(std::string p)
{
  path.emplace_back(std::move(p));
}

const Style &DirectMusic::style(const Reference &id)
{
  for (auto &i : styles)
  {
    if (i.first == id.file)
      return i.second;
  }

  std::ifstream ifs = implCustomOpen(id.file);

  auto pos = ifs.tellg();
  ifs.seekg(0, std::ios::end);
  auto size = ifs.tellg() - pos;
  ifs.seekg(pos, std::ios::beg);

  std::vector<uint8_t> data(static_cast<size_t>(size));
  if (!ifs.read(reinterpret_cast<char *>(&data[0]), data.size()))
  {
    // handle error
    std::cerr << "Error: failed to read file.\n";
  }

  ifs.close();

  Riff r{data.data(), data.size()};
  Style stl(r);

  styles.emplace_back(id.file, std::move(stl));
  return styles.back().second;
}

const DlsCollection &DirectMusic::dlsCollection(const Reference &id)
{
  return dlsCollection(id.file);
}

const DlsCollection &DirectMusic::dlsCollection(const std::string &file)
{
  for (auto &i : dls)
  {
    if (i->first == file)
      return i->second;
  }
  std::ifstream ifs = implCustomOpen(file);

  auto pos = ifs.tellg();
  ifs.seekg(0, std::ios::end);
  auto size = ifs.tellg() - pos;
  ifs.seekg(pos, std::ios::beg);

  std::vector<uint8_t> data(static_cast<size_t>(size));
  if (!ifs.read(reinterpret_cast<char *>(&data[0]), data.size()))
  {
    // handle error
    std::cerr << "Error: failed to read file.\n";
  }

  ifs.close();

  Riff r{data.data(), data.size()};
  DlsCollection stl(r);

  dls.emplace_back(new std::pair<std::string, DlsCollection>(file, std::move(stl)));
  return dls.back()->second;
}

std::ifstream DirectMusic::implCustomOpen(std::string file) noexcept(false)
{
  std::ifstream ifs;
  file.erase(std::remove(file.begin(), file.end(), '\0'), file.end());

  for (auto &i : path)
  {
    std::string filepath = "";
    if (std::filesystem::exists(i + "\\" + file))
      filepath = i + "\\" + file;
    ifs.open(filepath, std::ios::binary);
    if (ifs.is_open())
    {
      return ifs;
    }
  }
}
