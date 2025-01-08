


void create_docx(const char* filename) {
    int error = 0;
    // Open a new ZIP archive for the .docx file
    zip_t* archive = zip_open(filename, ZIP_CREATE | ZIP_TRUNCATE, &error);
    if (!archive) {
        printf("Error: Failed to create .docx file.\n");
        return;
    }

    // Add [Content_Types].xml
    const char* content_types =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Types xmlns=\"http://schemas.openxmlformats.org/package/2006/content-types\">"
        "<Default Extension=\"xml\" ContentType=\"application/xml\"/>"
        "<Default Extension=\"rels\" ContentType=\"application/vnd.openxmlformats-package.relationships+xml\"/>"
        "<Override PartName=\"/word/document.xml\" ContentType=\"application/vnd.openxmlformats-officedocument.wordprocessingml.document.main+xml\"/>"
        "</Types>";
    zip_source_t* source = zip_source_buffer(archive, content_types, strlen(content_types), 0);
    zip_file_add(archive, "[Content_Types].xml", source, ZIP_FL_OVERWRITE);

    // Add _rels/.rels
    const char* rels =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\">"
        "<Relationship Id=\"rId1\" Type=\"http://schemas.openxmlformats.org/officeDocument/2006/relationships/officeDocument\" Target=\"word/document.xml\"/>"
        "</Relationships>";
    source = zip_source_buffer(archive, rels, strlen(rels), 0);
    zip_file_add(archive, "_rels/.rels", source, ZIP_FL_OVERWRITE);

    // Add word/document.xml
    const char* document_xml =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<w:document xmlns:w=\"http://schemas.openxmlformats.org/wordprocessingml/2006/main\">"
        "<w:body>"
        "<w:p><w:r><w:t>Hello, World!</w:t></w:r></w:p>"
        "</w:body>"
        "</w:document>";
    source = zip_source_buffer(archive, document_xml, strlen(document_xml), 0);
    zip_file_add(archive, "word/document.xml", source, ZIP_FL_OVERWRITE);

    // Add word/_rels/document.xml.rels
    const char* document_rels =
        "<?xml version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"?>"
        "<Relationships xmlns=\"http://schemas.openxmlformats.org/package/2006/relationships\"></Relationships>";
    source = zip_source_buffer(archive, document_rels, strlen(document_rels), 0);
    zip_file_add(archive, "word/_rels/document.xml.rels", source, ZIP_FL_OVERWRITE);

    // Close the archive
    zip_close(archive);
    printf("Successfully created %s!\n", filename);
}

int main() {
    create_docx("example.docx");
    return 0;
}