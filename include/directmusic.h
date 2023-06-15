#pragma once

#include "dlscollection.h"
#include "patternlist.h"
#include "segment.h"
#include "style.h"

#include <vector>



namespace Dx8
{

  /**
   * http://doc.51windows.net/Directx9_SDK/htm/directmusicfilestructures.htm
   */
  class DirectMusic final
  {
  public:
    DirectMusic();

    using StyleList = std::vector<std::pair<std::string, Style>>;
    using DlsList = std::vector<std::unique_ptr<std::pair<std::string, DlsCollection>>>;

    PatternList load(const Segment &s);
    PatternList load(std::string fsgt);

    void addPath(std::string path);

    const Style &style(const Reference &id);
    const DlsCollection &dlsCollection(const Reference &id);
    const DlsCollection &dlsCollection(const std::string &file);

    const StyleList &stlList() const { return styles; }
    const DlsList &dlsCollection() { return dls; }
    std::vector<std::string> getPath() const { return path; }

  private:
    StyleList styles;
    DlsList dls;
    std::vector<std::string> path;

    std::ifstream implCustomOpen(std::string file) noexcept(false);
  };

}
