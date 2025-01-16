-- Таблица для хранения информации о пользователях
CREATE TABLE users (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор пользователя
    username VARCHAR(255) NOT NULL UNIQUE, -- Имя пользователя, должно быть уникальным
    email VARCHAR(255) NOT NULL UNIQUE, -- Электронная почта пользователя, должна быть уникальной
    password VARCHAR(255) NOT NULL, -- Пароль пользователя
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- Дата и время создания записи
);

-- Индексы для таблицы users
CREATE INDEX idx_users_username ON users(username);
CREATE INDEX idx_users_email ON users(email);

CREATE TABLE IF NOT EXISTS nodes (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор узла
    hostname VARCHAR(255) NOT NULL UNIQUE, -- Имя узла, должно быть уникальным
    ip_address VARCHAR(15) NOT NULL UNIQUE, -- IP-адрес узла, должен быть уникальным
    os VARCHAR(100) NOT NULL, -- Операционная система узла
    status VARCHAR(50) DEFAULT 'unknown', -- Статус узла (например, активен, неактивен), по умолчанию 'unknown'
    сreated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время создания записи
    UNIQUE (hostname, ip_address) -- Сочетание имени и IP-адреса также должно быть уникальным
);

-- Создание индексов для таблицы nodes
CREATE INDEX IF NOT EXISTS idx_nodes_hostname ON nodes(hostname);
CREATE INDEX IF NOT EXISTS idx_nodes_ip_address ON nodes(ip_address);
CREATE INDEX IF NOT EXISTS idx_nodes_os ON nodes(os);

-- Таблица для хранения логов активности
CREATE TABLE logs (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор лога
    hostname VARCHAR(255) NOT NULL, -- Имя узла, к которому относится лог
    log_message TEXT NOT NULL, -- Текст сообщения лога
    log_level VARCHAR(50) DEFAULT 'info', -- Уровень логирования (например, info, warning, error), по умолчанию 'info'
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время создания записи
    FOREIGN KEY (hostname) REFERENCES nodes(hostname) ON DELETE CASCADE -- Внешний ключ на узел, при удалении узла удаляются логи
);

-- Индексы для таблицы logs
CREATE INDEX idx_logs_hostname ON logs(hostname);
CREATE INDEX idx_logs_log_level ON logs(log_level);

-- Таблица для хранения метрик мониторинга узлов
CREATE TABLE metrics (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор метрики
    hostname VARCHAR(255) NOT NULL, -- Имя узла, к которому относится метрика
    cpu_usage DECIMAL(5, 2) CHECK (cpu_usage >= 0 AND cpu_usage <= 100), -- Использование CPU в процентах, с проверкой допустимых значений
    total_cpu DECIMAL(5, 2) CHECK (total_cpu >= 0 AND total_cpu <= 100), -- Полный объем CPU в процентах
    memory_usage DECIMAL(5, 2) CHECK (memory_usage >= 0 AND memory_usage <= 100), -- Использование памяти в процентах, с проверкой допустимых значений
    total_memory DECIMAL(5, 2) CHECK (total_memory >= 0 AND total_memory <= 100), -- Полный объем памяти в процентах
    network_in_mbps DECIMAL(10, 2) CHECK (network_in_mbps >= 0), -- Входящий трафик в Мбит/с, с проверкой допустимых значений
    total_network_in_mbps DECIMAL(10, 2) CHECK (total_network_in_mbps >= 0), -- Полный объем входящего трафика в Мбит/с
    network_out_mbps DECIMAL(10, 2) CHECK (network_out_mbps >= 0), -- Исходящий трафик в Мбит/с, с проверкой допустимых значений
    total_network_out_mbps DECIMAL(10, 2) CHECK (total_network_out_mbps >= 0), -- Полный объем исходящего трафика в Мбит/с
    disk_usage_gb DECIMAL(15, 2) CHECK (disk_usage_gb >= 0), -- Используемый объем дискового пространства в ГБ
    total_disk_gb DECIMAL(15, 2) CHECK (total_disk_gb >= 0), -- Полный объем дискового пространства в ГБ
    collected_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время сбора метрики
    FOREIGN KEY (hostname) REFERENCES nodes(hostname) ON DELETE CASCADE -- Внешний ключ на узел, при удалении узла удаляются метрики
);

-- Индексы для таблицы metrics
CREATE INDEX idx_metrics_hostname ON metrics(hostname);
CREATE INDEX idx_metrics_collected_at ON metrics(collected_at);