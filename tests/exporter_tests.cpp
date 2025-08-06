/**
 * @file exporter_tests.cpp
 * @brief Tests for the Exporter classes
 */

#include <gtest/gtest.h>
#include <tabulix/tabulix.hpp>
#include <tabulix/export/exporter.hpp>
#include <memory>

TEST(ExporterTest, Factory) {
    // Test that the factory creates the correct exporter types
    std::unique_ptr<tabulix::Exporter> textExporter = tabulix::Exporter::create(tabulix::ExportFormat::TEXT);
    std::unique_ptr<tabulix::Exporter> markdownExporter = tabulix::Exporter::create(tabulix::ExportFormat::MARKDOWN);
    std::unique_ptr<tabulix::Exporter> htmlExporter = tabulix::Exporter::create(tabulix::ExportFormat::HTML);
    std::unique_ptr<tabulix::Exporter> csvExporter = tabulix::Exporter::create(tabulix::ExportFormat::CSV);
    std::unique_ptr<tabulix::Exporter> jsonExporter = tabulix::Exporter::create(tabulix::ExportFormat::JSON);

    EXPECT_NE(textExporter, nullptr);
    EXPECT_NE(markdownExporter, nullptr);
    EXPECT_NE(htmlExporter, nullptr);
    EXPECT_NE(csvExporter, nullptr);
    EXPECT_NE(jsonExporter, nullptr);
}

TEST(ExporterTest, TextExporter) {
    tabulix::Table table;
    table.addHeader({"Col1", "Col2"});
    table.addRow({"A", "B"});

    std::unique_ptr<tabulix::Exporter> exporter = tabulix::Exporter::create(tabulix::ExportFormat::TEXT);
    std::string output = exporter->toString(table);

    // The text exporter should match the table's str() method
    EXPECT_EQ(output, table.str());
}

TEST(ExporterTest, MarkdownExporter) {
    tabulix::Table table;
    table.addHeader({"Col1", "Col2"});
    table.addRow({"A", "B"});

    std::unique_ptr<tabulix::Exporter> exporter = tabulix::Exporter::create(tabulix::ExportFormat::MARKDOWN);
    std::string output = exporter->toString(table);

    // Simple check that the output contains pipe characters which are used in markdown tables
    EXPECT_NE(output.find("|"), std::string::npos);
}

TEST(ExporterTest, EmptyTable) {
    tabulix::Table emptyTable;

    std::unique_ptr<tabulix::Exporter> textExporter = tabulix::Exporter::create(tabulix::ExportFormat::TEXT);
    std::unique_ptr<tabulix::Exporter> markdownExporter = tabulix::Exporter::create(tabulix::ExportFormat::MARKDOWN);
    std::unique_ptr<tabulix::Exporter> htmlExporter = tabulix::Exporter::create(tabulix::ExportFormat::HTML);
    std::unique_ptr<tabulix::Exporter> csvExporter = tabulix::Exporter::create(tabulix::ExportFormat::CSV);
    std::unique_ptr<tabulix::Exporter> jsonExporter = tabulix::Exporter::create(tabulix::ExportFormat::JSON);

    // Exporters should handle empty tables without crashing
    EXPECT_NO_THROW(textExporter->toString(emptyTable));
    EXPECT_NO_THROW(markdownExporter->toString(emptyTable));
    EXPECT_NO_THROW(htmlExporter->toString(emptyTable));
    EXPECT_NO_THROW(csvExporter->toString(emptyTable));
    EXPECT_NO_THROW(jsonExporter->toString(emptyTable));
}
