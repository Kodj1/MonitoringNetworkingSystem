-- Таблица для хранения информации о пользователях
CREATE TABLE users (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор пользователя
    username VARCHAR(255) NOT NULL UNIQUE, -- Имя пользователя, должно быть уникальным
    email VARCHAR(255) NOT NULL UNIQUE, -- Электронная почта пользователя, должна быть уникальной
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP -- Дата и время создания записи
);

-- Таблица для хранения информации о сетевых узлах
CREATE TABLE nodes (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор узла
    name VARCHAR(255) NOT NULL, -- Имя узла
    ip_address VARCHAR(15) NOT NULL UNIQUE, -- IP-адрес узла, должен быть уникальным
    status VARCHAR(50) DEFAULT 'unknown', -- Статус узла (например, активен, неактивен), по умолчанию 'unknown'
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время создания записи
    UNIQUE (name, ip_address) -- Сочетание имени и IP-адреса также должно быть уникальным
);

-- Таблица для хранения информации о соединениях между узлами
CREATE TABLE connections (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор соединения
    node1_id INT NOT NULL, -- Идентификатор первого узла
    node2_id INT NOT NULL, -- Идентификатор второго узла
    status VARCHAR(50) DEFAULT 'inactive', -- Статус соединения (например, активно, неактивно), по умолчанию 'inactive'
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время создания записи
    FOREIGN KEY (node1_id) REFERENCES nodes(id) ON DELETE CASCADE, -- Внешний ключ на первый узел, при удалении узла удаляется соединение
    FOREIGN KEY (node2_id) REFERENCES nodes(id) ON DELETE CASCADE, -- Внешний ключ на второй узел, при удалении узла удаляется соединение
    UNIQUE (node1_id, node2_id) -- Уникальность сочетания узлов
);

-- Таблица для хранения логов активности
CREATE TABLE logs (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор лога
    node_id INT NOT NULL, -- Идентификатор узла, к которому относится лог
    log_message TEXT NOT NULL, -- Текст сообщения лога
    log_level VARCHAR(50) DEFAULT 'info', -- Уровень логирования (например, info, warning, error), по умолчанию 'info'
    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время создания записи
    FOREIGN KEY (node_id) REFERENCES nodes(id) ON DELETE CASCADE -- Внешний ключ на узел, при удалении узла удаляются логи
);

-- Таблица для хранения метрик мониторинга узлов
CREATE TABLE metrics (
    id SERIAL PRIMARY KEY, -- Уникальный идентификатор метрики
    node_id INT NOT NULL, -- Идентификатор узла, к которому относится метрика
    cpu_usage DECIMAL(5, 2) CHECK (cpu_usage >= 0 AND cpu_usage <= 100), -- Использование CPU в процентах, с проверкой допустимых значений
    memory_usage DECIMAL(5, 2) CHECK (memory_usage >= 0 AND memory_usage <= 100), -- Использование памяти в процентах, с проверкой допустимых значений
    network_in DECIMAL(10, 2) CHECK (network_in >= 0), -- Входящий трафик в байтах, с проверкой допустимых значений
    network_out DECIMAL(10, 2) CHECK (network_out >= 0), -- Исходящий трафик в байтах, с проверкой допустимых значений
    collected_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP, -- Дата и время сбора метрики
    FOREIGN KEY (node_id) REFERENCES nodes(id) ON DELETE CASCADE -- Внешний ключ на узел, при удалении узла удаляются метрики
);

-- Индексы для ускорения поиска
CREATE INDEX idx_nodes_name ON nodes(name);
CREATE INDEX idx_nodes_ip_address ON nodes(ip_address);
CREATE INDEX idx_connections_node1_id ON connections(node1_id);
CREATE INDEX idx_connections_node2_id ON connections(node2_id);
CREATE INDEX idx_logs_node_id ON logs(node_id);
CREATE INDEX idx_metrics_node_id ON metrics(node_id);