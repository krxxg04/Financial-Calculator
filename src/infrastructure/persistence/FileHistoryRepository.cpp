#include "infrastructure/persistence/FileHistoryRepository.h"

#include <fstream>
#include <sstream>
#include <stdexcept>

namespace finance::infrastructure::persistence {

FileHistoryRepository::FileHistoryRepository(std::string filePath) : filePath_(std::move(filePath)) {}

void FileHistoryRepository::save(const domain::entities::CalculationResult& result) {
    std::ofstream out(filePath_, std::ios::app);
    if (!out.is_open()) {
        throw std::runtime_error("No se pudo abrir el archivo de historial para escritura.");
    }

    out << sanitizeField(result.timestamp()) << "|"
        << sanitizeField(result.operation()) << "|"
        << sanitizeField(result.inputSummary()) << "|"
        << sanitizeField(result.outputSummary()) << '\n';
}

std::vector<domain::entities::CalculationResult> FileHistoryRepository::loadAll() const {
    std::ifstream in(filePath_);
    if (!in.is_open()) {
        return {};
    }

    std::vector<domain::entities::CalculationResult> records;
    std::string line;
    while (std::getline(in, line)) {
        if (line.empty()) {
            continue;
        }

        const auto fields = split(line, '|');
        if (fields.size() != 4) {
            continue;
        }

        records.emplace_back(fields[1], fields[2], fields[3], fields[0]);
    }

    return records;
}

std::string FileHistoryRepository::sanitizeField(const std::string& text) {
    std::string sanitized = text;
    for (char& c : sanitized) {
        if (c == '|') {
            c = '/';
        }
        if (c == '\n' || c == '\r') {
            c = ' ';
        }
    }
    return sanitized;
}

std::vector<std::string> FileHistoryRepository::split(const std::string& line, char separator) {
    std::vector<std::string> parts;
    std::stringstream ss(line);
    std::string token;
    while (std::getline(ss, token, separator)) {
        parts.push_back(token);
    }
    return parts;
}

}  // namespace finance::infrastructure::persistence
