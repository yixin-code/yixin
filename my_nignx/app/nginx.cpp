#include <iostream>
#include <unistd.h>
#include "ngx_conf.h"
#include "ngx_func.h"
#include "ngx_global.h"

static void free_resource();

char *g_p_environ = nullptr; // 环境变量
int g_environ_len = 0; // 环境变量字节数
char **g_p_argv   = nullptr; // 命令行参数
pid_t ngx_pid     = 0;

int main(int argc, char *argv[]) {
    int ret_code = 0; // 退出代码0表示正常退出
    ngx_pid = getpid();
    g_p_argv = argv;

    CConfig *p_config = CConfig::get_instance();
    if (p_config->load_config("./nginx.conf") == false) {
        ngx_log_stderr(0, "配置文件[%s]载入失败", "nginx.conf");
        ret_code = 2; // No such file or directory 文件不存在
        goto fly;
    }

    ngx_log_init(); // 打开初始化日志
    if (ngx_init_signal() == -1) {
        ret_code = 1;
        goto fly;
    }

    save_environ();
    set_process_title("nginx: master process");

fly:
    free_resource();
    std::cout << "program exit\n";
    return ret_code;
}

void free_resource() {
    if (g_p_environ != nullptr) {
        delete[] g_p_environ;
        g_p_environ = nullptr;
    }

    if (log_t.m_fd != STDERR_FILENO && log_t.m_fd != -1) {
        close(log_t.m_fd);
        log_t.m_fd = -1; // 防止重复释放
    }
}