/**
 * @file exporter.hpp
 * @brief Definition of the Exporter class and export formats
 */

#ifndef TABULIX_EXPORT_EXPORTER_HPP
#define TABULIX_EXPORT_EXPORTER_HPP

#include <string>
#include <fstream>
#include <memory>
#include "../core/table.hpp"

namespace tabulix {

/**
 * @enum ExportFormat
 * @brief Supported export formats
 */
enum class ExportFormat {
    TEXT,     ///< Plain text
    MARKDOWN, ///< Markdown table
    HTML,     ///< HTML table
    CSV,      ///< Comma-separated values
    JSON      ///< JSON format
};

/**
 * @class Exporter
 * @brief Abstract base class for table exporters
 */
class Exporter {
public:
    /**
     * @brief Virtual destructor
     */
    virtual ~Exporter() = default;

    /**
     * @brief Export a table to a string
     * @param table Table to export
     * @return Exported table as string
     */
    [[nodiscard]] virtual std::string toString(const Table& table) const = 0;

    /**
     * @brief Export a table to a file
     * @param table Table to export
     * @param filename Path to the output file
     * @return true if export was successful, false otherwise
     */
    virtual bool toFile(const Table& table, const std::string& filename) const;

    /**
     * @brief Factory method to create an exporter for a specific format
     * @param format Export format
     * @return Unique pointer to an exporter instance
     */
    static std::unique_ptr<Exporter> create(ExportFormat format);
};

/**
 * @class TextExporter
 * @brief Exports tables in plain text format
 */
class TextExporter : public Exporter {
public:
    /**
     * @brief Export a table to a string in plain text format
     * @param table Table to export
     * @return Exported table as string
     */
    [[nodiscard]] std::string toString(const Table& table) const override;
};

/**
 * @class MarkdownExporter
 * @brief Exports tables in Markdown format
 */
class MarkdownExporter : public Exporter {
public:
    /**
     * @brief Export a table to a string in Markdown format
     * @param table Table to export
     * @return Exported table as string
     */
    [[nodiscard]] std::string toString(const Table& table) const override;
};

/**
 * @class HtmlExporter
 * @brief Exports tables in HTML format
 */
class HtmlExporter : public Exporter {
public:
    /**
     * @brief Export a table to a string in HTML format
     * @param table Table to export
     * @return Exported table as string
     */
    [[nodiscard]] std::string toString(const Table& table) const override;
};

/**
 * @class CsvExporter
 * @brief Exports tables in CSV format
 */
class CsvExporter : public Exporter {
public:
    /**
     * @brief Constructor
     * @param delimiter Field delimiter (default is comma)
     */
    explicit CsvExporter(char delimiter = ',');

    /**
     * @brief Export a table to a string in CSV format
     * @param table Table to export
     * @return Exported table as string
     */
    [[nodiscard]] std::string toString(const Table& table) const override;

private:
    char m_delimiter;
};

/**
 * @class JsonExporter
 * @brief Exports tables in JSON format
 */
class JsonExporter : public Exporter {
public:
    /**
     * @brief Export a table to a string in JSON format
     * @param table Table to export
     * @return Exported table as string
     */
    [[nodiscard]] std::string toString(const Table& table) const override;
};

} // namespace tabulix

#endif // TABULIX_EXPORT_EXPORTER_HPP
