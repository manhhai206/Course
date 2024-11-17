# Tên của chương trình
TARGET = run

# Thư mục chứa header và source files
HEADER_DIR = Inc
SOURCE_DIR = Src

# Các tệp nguồn và tệp object tương ứng
SOURCES = $(wildcard $(SOURCE_DIR)/*.c)  # Sử dụng .c cho C
OBJECTS = $(SOURCES:.c=.o)

# Trình biên dịch và các cờ
CC = gcc  # Sử dụng gcc cho C
CFLAGS = -I$(HEADER_DIR) -Wall -Wextra

# Quy tắc đầu tiên là quy tắc mặc định sẽ được thực thi
all: $(TARGET)

# Quy tắc để tạo ra tệp thực thi
$(TARGET): $(OBJECTS)
	$(CC) -o $@ $^

# Quy tắc để biên dịch các tệp .c thành .o
$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

# Quy tắc để làm sạch thư mục build
clean:
	rm -f $(SOURCE_DIR)/*.o $(TARGET)

# Mục tiêu giả (phony target)
.PHONY: all clean
