#include"CreateDocxFiles.hxx"

int main() {
	FILE* fp;
	FILE* NFile;
	
	fp = fopen("C:\\Users\\Admin\\source\\repos\\CreateDocxFiles\\CreateDocxFiles.csv", "a+");
	char FileLine[200];
	char* DSName;
	char* FileExten;
	char* FileName;
	char* owner;

	while (fgets(FileLine, 200, fp)) {
		
		DSName = strtok(FileLine, ",");
		FileExten = strtok(NULL, ",");
		FileName = strtok(NULL, ",");
		owner = strtok(NULL, "\n");

		
		NFile = fopen(FileName, "a+");
		fputs("File Name: ", NFile);
		fputs(DSName, NFile);

		fclose(NFile);
	}	
	
	fclose(fp);
	(void)_getch();
	return 0;
}