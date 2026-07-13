#pragma once

#include "external.hpp"

namespace cne
{
	class FileManager
	{
	public:
		//struct MyData
		//{
		//	int id;
		//	std::string name;
		//	std::vector<float> values;

		//	// 序列化函数
		//	template <class Archive>
		//	void serialize(Archive& ar) {
		//		ar(id, name, values); // 二进制存档中无需 CEREAL_NVP
		//}自定义二进制文件实例

		// 写入二进制文件
		template <typename T>
		void WriteBinary(std::string path, T data)
		{
			std::ofstream ofs(path, std::ios::binary);
			cereal::BinaryOutputArchive archive(ofs);
			archive(data);
		}

		// 读取二进制文件
		template <typename T>
		void ReadBinary(std::string path, T& data)
		{
			std::ifstream ifs(path, std::ios::binary);
			cereal::BinaryInputArchive archive(ifs);
			archive(data);
		}

		// 写入JSON（指定键名）
		void WriteJson(std::string path, const Json& data, std::string name, int indent = 4);

		// 写入JSON（全局）
		void WriteJson(std::string path, const Json& data, int indent = 4);

		// 读取JSON（指定键名），成功返回true，失败时outData不变或置空
		void ReadJson(std::string path, Json& outData, std::string name);

		// 读取JSON（全局），成功返回true，失败时outData不变
		void ReadJson(std::string path, Json& outData);

		FileManager(const FileManager&) = delete;
		FileManager& operator=(const FileManager&) = delete;
		static FileManager* Instance()
		{
			if (instance_ == nullptr)
			{
				instance_ = new FileManager;
			}
			return instance_;
		}
	private:
		FileManager() = default;
		~FileManager() = default;
		static FileManager* instance_;
	};
}