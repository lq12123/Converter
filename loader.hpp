#ifndef LOADER_H
#define LOADER_H

#include <utility>
#include <QFontDatabase>
#include <QDebug>

class Loader
{
public:
    Loader() = default;

    template<typename T, typename... Args>
    static void loadFont(T const& arg, Args const&... args) noexcept;

    template<typename T>
    static void loadFont(T const&& fontName) noexcept;

    template<typename T, typename... Args>
    static void loadFont(T const&& arg, Args const&&... args) noexcept;

    static decltype(auto) getLoadedFonts() noexcept;
};

template<typename T>
void Loader::loadFont(T const&& fontName) noexcept
{
    try
    {
        int font_id = QFontDatabase::addApplicationFont(fontName);
        if (font_id == -1)
            qDebug() << QString("[-] %1 font not loaded.").arg(fontName);
        else
            qDebug() << QString("[+] %1 font loaded.").arg(fontName);
    }
    catch(...) {}
}

template<typename T, typename... Args>
void Loader::loadFont(T const&& arg, Args const&&... args) noexcept
{

    loadFont(std::move(arg));
    loadFont(std::move(args)...);
}

template<typename T, typename... Args>
void Loader::loadFont(T const& arg, Args const&... args) noexcept
{
    loadFont(std::move(arg), std::move(args)...);
}

#endif // LOADER_H
